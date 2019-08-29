#include <math.h>
#include <iostream>
#include <omp.h>

#include <tarzann/ComputeStrategy.h>
#include <tarzann/Connection.h>
#include <tarzann/Debug.h>
#include <tarzann/FeaturalReceptiveField.h>
#include <tarzann/GammaUnits.h>
#include <tarzann/GatingSignal.h>
#include <tarzann/Layer.h>
#include <tarzann/Matrix.h>
#include <tarzann/PLattice.h>
#include <tarzann/ReceptiveField.h>
#include <tarzann/Sheet.h>

using namespace std;
using namespace tarzann;

ComputeStrategy::ComputeStrategy(TaskType task_type,
                                 int steps_per_attentive_cycle,
                                 PLattice* plattice)
{
    m_plattice = plattice;

    m_control_signal_generator = new ControlSignalGenerator(steps_per_attentive_cycle,
                                                            task_type);

    m_theta_competition = 0.1;
    m_clock_time = 0;
}

ComputeStrategy::~ComputeStrategy()
{
    delete m_control_signal_generator;
}

void ComputeStrategy::run()
{
    //update the clock
    ControlSignal signal = m_control_signal_generator->updateTimer();

    //get the time
    m_clock_time = m_control_signal_generator->getTime();

    //print
    cout << endl;
    cout << "t = " << std::to_string(m_clock_time) << endl;
    signal.print();

    //memory
    std::vector<Layer*> layers;
    std::vector<Sheet*> sheets;

    //start processing
    m_plattice->getLayers(layers);
    int num_layers = (int) layers.size();

    if(signal.m_do_next_fixation)
    {
        for (int i=0; i<num_layers; i++)
        {
            Layer* layer = layers[i];
            layer->getSheets(sheets);
            int num_sheets = (int) sheets.size();

            for (int j=0; j<num_sheets; j++)
            {
                Sheet* sheet = sheets[j];
                sheet->resetGatingUnits();
            }
        }
    }

    for (int i=0; i<num_layers; i++)
    {
        Layer* layer = layers[i];
        layer->getSheets(sheets);
        int num_sheets = (int) sheets.size();

        #pragma omp parallel for num_threads(6)
        for (int j=0; j<num_sheets; j++)
        {
            Sheet* sheet = sheets[j];

            if(signal.m_do_find_winner)
            {
                if(layer->getType() == TOP_LAYER)
                {
                    sheet->findWinner();
                }
            }

            processSheet(sheet);
        }
    }
}

void ComputeStrategy::processSheet(Sheet* sheet)
{
    //get connection information
    std::vector<Connection*> connections;
    std::vector<ReceptiveField*> receptive_field_buffers;
    std::vector<Matrix*> input_matrix_buffers;
    std::vector<FeaturalReceptiveField*> frf;
    std::vector<Filter*> filter;
    std::vector<SheetMapping> src_dst_mapping;
    std::vector<SheetMapping> dst_src_mapping;
    std::vector<int> rf_width;
    std::vector<int> rf_height;

    int max_rf_width = 0;
    int max_rf_height = 0;

    //flags for competition
    Matrix* competition_flags = sheet->getCompetitionFlags();

    //the buffer new outputs will be written to
    Matrix* output = sheet->getConvolvedInputs();
    SheetType sheet_type = sheet->getSheetType();
    if(sheet_type == sum_sheet)
        output->setValue(0.0);
    else if (sheet_type == mul_sheet)
        output->setValue(1.0);

    //suppressive surround
    Matrix* suppressive_surround = sheet->getSuppressiveSurround();

    //gating control
    Matrix* gating_control = sheet->getGatingControl();

    InputToNeuron* inputs_to_neuron_buffer = (InputToNeuron*) sheet->getBuffer()->getData();
    int num_inputs_to_neurons = 0;

    //get all the connections
    sheet->getInputConnections(connections);
    int num_connections = (int) connections.size();

    //store the connection information (receptive fields and sources)
    for(int i=0; i<num_connections; i++)
    {
        Connection* connection = (Connection*) connections[i];

        receptive_field_buffers.push_back(connection->getReceptiveField());

        input_matrix_buffers.push_back(connection->getSource()->getOutput());

        frf.push_back(connection->getReceptiveField()->getFeaturalRFBuffer());

        filter.push_back(connection->getReceptiveField()->getFilter());

        rf_width.push_back(connection->getReceptiveField()->getFilter()->getXSize());

        rf_height.push_back(connection->getReceptiveField()->getFilter()->getYSize());

        src_dst_mapping.push_back(connection->getSrcDstMapping());

        dst_src_mapping.push_back(connection->getDstSrcMapping());

        max_rf_width = max(rf_width[i],max_rf_width);

        max_rf_height = max(rf_height[i],max_rf_height);
    }

    //variables
    int dst_width = (int) sheet->getWidth();
    int dst_height = (int) sheet->getHeight();
    float suppression_weight;
    float gc;
    float do_competition;

    //compute gating control signals
    if(sheet->getLayerType() != TOP_LAYER)
        sheet->updateGatingControl();


    //process the inputs to each neuron
    if(num_connections>0)
    {
        for(int y=0;y<dst_height;y++)
        {
            for(int x=0; x<dst_width;x++)
            {
                suppression_weight = (*suppressive_surround)(x,y);

                gc = (*gating_control)(x,y);
                do_competition = (*competition_flags)(x,y);

                num_inputs_to_neurons = 0;

                //load the inputs into the receptive field buffers
                for(int i=0; i<num_connections; i++)
                {
                    getInputWeights(input_matrix_buffers[i],
                                    output,
                                    filter[i],
                                    frf[i],
                                    x,
                                    y,
                                    dst_src_mapping[i]);

                    frf[i]->setGammas(1.0);
                }
                //do competition if we must
                if((gc==1.0 || gc==-1.0) && do_competition!=1.0)
                {
                    int connection_id;

                    //load all inputs into linear memory
                    loadConnectionsIntoBuffer(connections,
                                              inputs_to_neuron_buffer,
                                              num_inputs_to_neurons);

                    //perform competition on linear memory
                    if(gc==1.0)
                    {
                        wtaCompetition(inputs_to_neuron_buffer,
                                       num_inputs_to_neurons,
                                       m_theta_competition);
                    }

                    //update gamma units and output gating signals
                    bool gamma_bit;
                    GammaUnits* gu;
                    InputToNeuron* input_to_neuron;

                    for(int i=0; i<num_connections; i++)
                    {
                        gu = connections[i]->getGammaUnits();
                        gu->seekUnit(x,y);
                    }

                    for (int i=0; i<num_inputs_to_neurons; i++)
                    {
                        input_to_neuron = inputs_to_neuron_buffer + i;
                        connection_id = input_to_neuron->m_connection_id;

                        if(input_to_neuron->m_gamma > 0.0)
                            gamma_bit = true;
                        else
                            gamma_bit = false;

                        gu = connections[connection_id]->getGammaUnits();
                        gu->writeBit(gamma_bit);
                    }

                    //updated outgoing gating signals
                    for (int i=0; i<num_connections; i++)
                    {
                        gu = connections[i]->getGammaUnits();
                        gu->flushBits();
                        connections[i]->getGatingSignal()->updateGatingSignal(gu,
                                                                              dst_src_mapping[i],
                                                                              x,
                                                                              y);
                    }

                    //change competition flag
                    (*competition_flags)(x,y) = 1.0;
                }


                //suppress selected inputs - change gammas
                else if (gc==1.0)
                {
                    for(int i=0; i<num_connections; i++)
                    {
                        frf[i]->loadGammaUnits(connections[i]->getGammaUnits(),
                                               x,
                                               y,
                                               suppression_weight);
                    }
                }
                //suppress all inputs - change all gammas
                else if (gc==-1.0)
                {
                    for(int i=0; i<num_connections; i++)
                    {
                        frf[i]->setGammas(0.0);
                    }
                }

                if (sheet_type == sum_sheet)
                {
                    //sum the inputs
                    for(int i=0; i<num_connections; i++)
                    {
                        (*output)(x,y) += sumInputWeights(frf[i]);
                    }
                }
                else if(sheet_type == mul_sheet)
                {
                    //multiply the inputs
                    for(int i=0; i<num_connections; i++)
                    {
                        (*output)(x,y) *= sumInputWeights(frf[i]);
                    }
                }

            }
        }

        //update neuron outputs
        sheet->computeNeuralResponse(m_clock_time);
    }
}

void ComputeStrategy::wtaCompetition(InputToNeuron* buffer, int n, float theta)
{
    for (int i=0; i<6; i++)
    {
        wtaComputeSumOfDeltas(buffer,n,theta);
        wtaUpdateActivations(buffer,n);
    }
    wtaUpdateGammas(buffer,n);
}

void ComputeStrategy::wtaComputeSumOfDeltas(InputToNeuron* buffer, int n, float theta)
{
    float activity_i;
    float activity_j;
    float delta;

    for(int i=0; i<n; i++)
    {
        (buffer+i)->m_sum_of_deltas = 0.0;
    }

    for(int i=0; i<n; i++)
    {
        activity_i = (buffer+i)->m_r_prime * (buffer+i)->m_g;

        for(int j=0; j<n; j++)
        {
            activity_j = (buffer+j)->m_r_prime * (buffer+j)->m_g;

            if(i!=j)
            {
                delta = activity_j - activity_i;

                if(delta < 0.0001 && delta > 0.0001)
                    delta = 0.0;
                if(delta > theta)
                    (buffer+i)->m_sum_of_deltas += delta;
            }
        }
    }
}

void ComputeStrategy::wtaUpdateActivations(InputToNeuron* buffer, int n)
{
    float r_prime;

    for(int i=0; i<n; i++)
    {
        //current
        r_prime = (buffer+i)->m_r_prime;
        r_prime = r_prime - (buffer+i)->m_sum_of_deltas;

        //apply rectification
        r_prime = r_prime + fabs(r_prime);
        r_prime *= 0.5;

        (buffer+i)->m_r_prime = r_prime;
    }
}

void ComputeStrategy::wtaUpdateGammas(InputToNeuron* buffer, int n)
{
    float r;
    for(int i=0; i<n; i++)
    {
        r = (buffer+i)->m_r;
        if (r!=0.0)
            (buffer+i)->m_gamma = (buffer+i)->m_r_prime/(buffer+i)->m_r;
        else
            (buffer+i)->m_gamma = 0.0;
    }
}

void ComputeStrategy::loadConnectionsIntoBuffer(std::vector<Connection*> connections,
                                                InputToNeuron* buffer_ptr,
                                                int& n)
{
    n=0;
    int num_connections = (int) connections.size();
    InputToNeuron* buffer = buffer_ptr;
    Connection* connection;
    FeaturalReceptiveField* frf;

    for(int i=0; i<num_connections; i++)
    {
        connection = (Connection*) connections[i];
        frf = connection->getReceptiveField()->getFeaturalRFBuffer();
        int rf_width = frf->m_width;
        int rf_height = frf->m_height;

        for(int y=0; y<rf_height; y++)
        {
            for(int x=0; x<rf_width; x++)
            {
                //copy info into temp memory
                buffer->m_g = frf->m_g[y][x];
                buffer->m_r = frf->m_r[y][x];
                buffer->m_r_prime = buffer->m_r;
                buffer->m_sum_of_deltas = 0.0;
                buffer->m_gamma = 0.0;
                buffer->m_connection_id = i;
                buffer->m_shift_x = x - rf_width/2;
                buffer->m_shift_y = y - rf_height/2;

                //copy into memory
                buffer++;
                n++;
            };
        }
    }
}

float ComputeStrategy::sumInputWeights(FeaturalReceptiveField* featural_rf)
{
    float sum = 0.0;

    for (int i=0; i<featural_rf->m_height; i++)
    {
        for (int j=0; j<featural_rf->m_width; j++)
        {
            sum += featural_rf->m_g[i][j]*featural_rf->m_r[i][j]*
                   featural_rf->m_gammas[i][j];
        }
    }

    return sum;
}

void ComputeStrategy::getInputWeights(Matrix* input,
                                      Matrix* output,
                                      Filter* filter,
                                      FeaturalReceptiveField* frf,
                                      int x,
                                      int y,
                                      SheetMapping mapping)
{
    int src_width = input->getXSize();
    int src_height = input->getYSize();

    int cx = x + filter->getShiftX();
    int cy = y + filter->getShiftY();

    int rf_width = filter->getXSize();
    int rf_height = filter->getYSize();

    int ix;
    int iy;

    int left = cx - rf_width/2;
    int right = cx + rf_width/2;
    int top = cy - rf_height/2;
    int bottom = cy + rf_height/2;

    for (y = top; y<=bottom; y++)
    {
        for (x = left; x <= right; x++)
        {
            ix = ((float) x) * mapping.m_scale_x;
            iy = ((float) y) * mapping.m_scale_y;

            if (ix < 0)
                ix = 0;
            else if (ix > (src_width - 1))
                ix = (src_width - 1);

            if (iy < 0)
                iy = 0;
            else if (iy > (src_height - 1))
                iy = (src_height - 1);

            frf->m_g[y-top][x-left] = (*filter)(x-left,y-top);
            frf->m_r[y-top][x-left] = (*input)(ix,iy);
        }
    }
}
