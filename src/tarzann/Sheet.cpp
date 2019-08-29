#include <list>

#include <tarzann/Connection.h>
#include <tarzann/GatingSignal.h>
#include <tarzann/GammaUnits.h>
#include <tarzann/Sheet.h>
#include <tarzann/Matrix.h>

using namespace tarzann;

Sheet::Sheet(std::string sheet_name,
             uint32_t width,
             uint32_t height,
             NeuronType neuron_type,
             LayerType layer_type)
{
    m_name = sheet_name;
    m_width = width;
    m_height = height;
    m_layer_type = layer_type;
    m_sheet_type = sum_sheet; // Set the default sheet type to sum

    m_feature_bias = 1.0;

    m_output = std::tr1::shared_ptr<Matrix>
                (new Matrix(m_width, m_height));

    m_labels = std::tr1::shared_ptr<Matrix>
                (new Matrix(m_width, m_height));

    m_h_currs=std::tr1::shared_ptr<Array2D<H_curr>>
                        (new Array2D<H_curr>(m_width,m_height));

    m_spatial_bias = std::tr1::shared_ptr<Matrix>
                    ( new Matrix(m_width, m_height) );

    m_spatial_bias->setValue(1.0);

    m_competition_flags = std::tr1::shared_ptr<Matrix>
                ( new Matrix(m_width, m_height) );

    m_competition_flags->setValue(0.0);

    m_buffer = std::tr1::shared_ptr<Matrix>
            ( new Matrix(1024, 1024) );

    //Gating control - all input gating signals are processed and stored here
    //to determine control for competition.
    m_gating_control = std::tr1::shared_ptr<Matrix>
                        (new Matrix(m_width, m_height));

    m_gating_control->setValue(0.0);

    //This buffer stores the latest convolved inputs.
    //It is passed through the neurons to get new activations.
    m_convolved_input=std::tr1::shared_ptr<Matrix>
                (new Matrix(m_width, m_height));

    m_convolved_input->setValue(0.0);

    //IOR map
    m_ior_map = std::tr1::shared_ptr<Matrix>
                (new Matrix(m_width, m_height));

    m_ior_map->setValue(0.0);

    //suppressive surround
    m_suppressive_surround = std::tr1::shared_ptr<Matrix>
            (new Matrix(m_width, m_height));

    m_suppressive_surround->setValue(1.0);

    //Setup the neurons
    createTheNeuron(neuron_type);
}

Sheet::Sheet(std::string sheet_name,
             uint32_t width,
             uint32_t height,
             NeuronType neuron_type,
             SheetType sheet_type,
             LayerType layer_type):\
    Sheet(sheet_name,width,height,
          neuron_type,layer_type)
{
    m_sheet_type = sheet_type;
}

Sheet::~Sheet()
{
    m_output_connections.clear();
    m_input_connections.clear();
}

LayerType Sheet::getLayerType()
{
    return m_layer_type;
}

SheetType Sheet::getSheetType()
{
    return m_sheet_type;
}

void Sheet::createTheNeuron(NeuronType neuron_type)
{
    switch (neuron_type)
    {
        case sigmoid_nrn:
            m_neuron= std::tr1::shared_ptr<NeuronSigmoid>
                    (new NeuronSigmoid(this));
            break;
        case st_nrn:
            m_neuron= std::tr1::shared_ptr<NeuronST>
                    (new NeuronST(this));
            break;
        case st_nrn_ih:
            m_neuron= std::tr1::shared_ptr<NeuronST1>
                    (new NeuronST1(this));
            break;

        case lif_nrn:
            break;

        case linear_nrn:
            m_neuron= std::tr1::shared_ptr<NeuronLinear>
                    (new NeuronLinear(this));

        case linear2_nrn:
            m_neuron= std::tr1::shared_ptr<NeuronLinear2>
                    (new NeuronLinear2(this));

        case no_nrn:
                break;
    }
}

void Sheet::computeNeuralResponse(uint32_t currnt_t)
{
    m_sheet_mutex.lock();
    m_neuron->ComputeActivation(currnt_t);
    m_sheet_mutex.unlock();
}

void Sheet::addInputGatingSignal(GatingSignal* g)
{
    m_input_gating_signals.push_back(g);

    std::tr1::shared_ptr<Connection> c =
            std::tr1::shared_ptr<Connection>
            (new Connection(this,g->getSourceSheet(),""));

    m_output_connections.push_back(c);
}

Connection* Sheet::createConnection(Sheet* src_sheet, std::string connection_name)
{
    //create the connection
    std::tr1::shared_ptr<Connection> c =
            std::tr1::shared_ptr<Connection>
            (new Connection(src_sheet,this,connection_name));

    //store the input connection
    m_input_connections.push_back(c);

    //add a reverse connection for selective tuning feedback
    Sheet* dst = c->getSource();

    //add to gating output list
    m_output_gating_signals.push_back(c->getGatingSignal());

    //add to input signals of destination sheet
    dst->addInputGatingSignal(c->getGatingSignal());

    //return the connection
    return c.get();
}

Matrix* Sheet::getOutput()
{
    return m_output.get();
}

Array2D<H_curr>* Sheet::getH_currs()
{
    return m_h_currs.get();
}

Matrix* Sheet::getBuffer()
{
    return m_buffer.get();
}

void Sheet::updateOutput()
{
    m_sheet_mutex.lock();
    m_output->copy(*m_convolved_input);
    m_sheet_mutex.unlock();
}

Matrix* Sheet::getSpatialBias()
{
    return m_spatial_bias.get();
}

void Sheet::setSpatialBias(Matrix* spatial_bias)
{
    *m_spatial_bias = *spatial_bias;
}

float Sheet::getFeatureBias()
{
    return m_feature_bias;
}

void Sheet::setFeatureBias(float feature_bias)
{
    m_feature_bias = feature_bias;
}

std::string Sheet::getName()
{
    return m_name;
}

Matrix* Sheet::getConvolvedInputs()
{
    return m_convolved_input.get();
}

uint32_t Sheet::getWidth()
{
    return m_width;
}

uint32_t Sheet::getHeight()
{
    return m_height;
}

Neuron* Sheet::getNeuron()
{
    return m_neuron.get();
}
void Sheet::getInputConnections(std::vector<Connection*>& connections)
{
    connections.clear();

    for (uint32_t i=0; i<m_input_connections.size(); i++)
    {
        connections.push_back(m_input_connections[i].get());
    }
}

void Sheet::getOutputConnections(std::vector<Connection*>& connections)
{
    connections.clear();

    for (uint32_t i=0; i<m_output_connections.size(); i++)
    {
        connections.push_back(m_output_connections[i].get());
    }
}

Matrix* Sheet::getCompetitionFlags()
{
    return m_competition_flags.get();
}

Matrix* Sheet::getGatingControl()
{
    return m_gating_control.get();
}

Matrix* Sheet::getIORMap()
{
    return m_ior_map.get();
}

Matrix* Sheet::getSuppressiveSurround()
{
    return m_suppressive_surround.get();
}

GatingSignal* Sheet::getInputGatingSignal(uint32_t index)
{
    return m_input_gating_signals[index];
}

void Sheet::resetGatingUnits()
{
    for (uint32_t i=0; i<m_input_connections.size(); i++)
    {
        Connection* connection = m_input_connections[i].get();

        //reset the gating signal
        GatingSignal* gating_signal = connection->getGatingSignal();
        Matrix* gating_signal_matrix = gating_signal->getGatingSignalMatrix();
        gating_signal_matrix->setValue(0.0);

        //reset the gamma units
        GammaUnits* gamma_units = connection->getGammaUnits();
        gamma_units->resetGammaUnits();
    }

    //update IOR map with gating control
    updateIORMap();

    //reset the gating control
    m_gating_control->setValue(0.0);

    //reset flags for doing selective tuning
    m_competition_flags->setValue(0.0);
}

void Sheet::updateIORMap()
{
    float gc;
    float ior;

    for(uint32_t i=0; i<m_height; i++)
    {
        for(uint32_t j=0; j<m_width; j++)
        {
            gc = (*m_gating_control)(j,i);
            ior = (*m_ior_map)(j,i);

            if(gc == 1.0)
            {
                if(ior == 0.0)
                {
                    (*m_ior_map)(j,i) = IOR_CYCLES;
                }
                else
                    (*m_ior_map)(j,i) -= 1.0;
            }
            else
            {
                if(ior > 0.0)
                {
                    (*m_ior_map)(j,i) -= 1.0;
                }
            }
        }
    }
}

void Sheet::findWinner()
{
    Winner winner = m_output->getMaxActivation(m_ior_map.get());

    (*m_gating_control)(winner.x,winner.y) = 1.0;
}

//find the largest regions of winners
void Sheet::findLargestContiguousRegion(Matrix* binary,
                                        Matrix* strength,
                                        Matrix* labels)
{
    std::vector<ObjectRegion> objects;
    labels->setValue(0);

    int dx[]={1,-1,0,0};
    int dy[]={0,0,1,-1};

    float id = 0;
    Point2D current_pt;
    float s;

    for (int y=0;y<m_height;y++)
    {
        for (int x=0;x<m_width;x++)
        {
            //if not labelled and is an object
            if ((*labels)(x,y) == 0.0 && (*binary)(x,y) == 1.0)
            {
                //list of points to examine
                std::list<Point2D> points;

                //init region object ID
                id+=1.0;
                (*labels)(x,y) = id;

                //init current object information
                ObjectRegion r;
                s = (*strength)(x,y);
                current_pt = Point2D(x,y);
                r.updateRegion(current_pt,s);

                //init point list
                points.push_back(current_pt);

                //flood fill
                while (!points.empty())
                {
                    int px = points.front().x;
                    int py = points.front().y;
                    points.pop_front();

                    for (int d=0;d<4;d++)
                    {
                        int ox = px+dx[d];
                        int oy = py+dy[d];

                        //printf("Neighbour points (%d,%d)\n",ox,oy);

                        if(ox>=0 && oy>=0 && ox<m_width && oy<m_height)
                        {
                            if((*labels)(ox,oy) == 0.0 && (*binary)(ox,oy) == 1.0)
                            {
                                //set the label
                                (*labels)(ox,oy) = id;
                                s = (*strength)(ox,oy);

                                //store neighbour
                                current_pt = Point2D(ox,oy);
                                points.push_back(current_pt);

                                //update region object
                                r.updateRegion(current_pt,s);
                            }
                        }
                    }
                }
                r.finalizeRegion();
                objects.push_back(r);
            }
        }
    }

    //update labels - set small regions to zero
    float max_id=-1;
    float max_strength=0.0;
    int num_objects = objects.size();

    //printf("Second competition stage - %d objects\n",num_objects);
    //std::cout<< "Number of labels" << id << std::endl;

    if(num_objects>=1)
    {
        for(int i=0; i<num_objects; i++)
        {
            if (objects[i].size>max_strength)
            {
                max_strength = objects[i].max_response;
                max_id = (float)i+1.0;
            }
        }

        //cut out small regions
        for (int y=1;y<m_height-1;y++)
        {
            for (int x=1;x<m_width-1;x++)
            {
                //if not labelled and is an object
                if ((*labels)(x,y)>0.0)
                {
                    if((*labels)(x,y)!=max_id)
                    {
                        (*labels)(x,y) = -1.0;
                        (*binary)(x,y) = -1.0;
                    }
                }
            }
        }

        //fill winner region
        max_id = max_id - 1;
        m_winner_region = objects[max_id];

        int cx = objects[max_id].center.x;
        int cy = objects[max_id].center.y;
        int radius = objects[max_id].radius;
        int dist;

        for (int y = (int) objects[max_id].rtop; y <= (int)objects[max_id].rbottom; y++)
        {
            for (int x = (int) objects[max_id].rleft; x <= (int) objects[max_id].rright; x++)
            {
                dist = (x-cx)*(x-cx);
                dist += (y-cy)*(y-cy);
                dist = sqrt(dist);
                if(dist<radius)
                {
                    (*binary)(x,y)=1.0;
                }
                else
                {
                    (*binary)(x,y)=-1.0;
                }
            }
        }
    }
    else
    {
        m_winner_region.reset();
    }
}

void Sheet::createSuppressiveSurround()
{
    //set to zero
    m_suppressive_surround->setValue(0.0);

    //winner sigma
    float sigma1 = m_winner_region.radius;
    float sigma2 = 1.5*m_winner_region.radius;

    if(sigma1>1.0 && sigma2>2.0)
    {
        float cx = m_winner_region.center.x;
        float cy = m_winner_region.center.y;

        float x1, y1;
        float co1 = 1.0/(2.0*M_PI*sigma1*sigma1);
        float co2 = 1.0/(2.0*M_PI*sigma2*sigma2);
        float gauss1;
        float gauss2;
        float gauss;

        for (int j=0; j<m_height; j++)
        {
            for (int i=0;i<m_width;i++)
            {
                //DoG value
                x1 = (float) i;
                y1 = (float) j;
                gauss1 = co1 * exp(-((x1-cx)*(x1-cx)+(y1-cy)*(y1-cy))/(2.0*sigma1*sigma1));
                gauss2 = co2 * exp(-((x1-cx)*(x1-cx)+(y1-cy)*(y1-cy))/(2.0*sigma2*sigma2));
                gauss = gauss1 - 2.5*gauss2;

                //store
                (*m_suppressive_surround)(i,j) = gauss;
            }
        }
        m_suppressive_surround->scaleValues(0.2,1.0);
    }
    else
    {
        m_suppressive_surround->setValue(1.0);
    }
}


void Sheet::updateGatingControl()
{
    float gating_signal;
    float gating_control;

    for (uint32_t i=0; i<m_width; i++)
    {
        for (uint32_t j=0; j<m_height; j++)
        {
            gating_control = 0.0;

            for (uint32_t idx=0; idx<m_input_gating_signals.size(); idx++)
            {
                gating_signal = (*getInputGatingSignal(idx)->getGatingSignalMatrix())(i,j);

                if (gating_signal>0.0)
                    gating_control = 1.0;
                else if (gating_signal<0.0 && gating_control<1.0)
                    gating_control = -1.0;
            }
            (*m_gating_control)(i,j) = gating_control;
        }
    }

    findLargestContiguousRegion(m_gating_control.get(),
                                m_output.get(),
                                m_labels.get());

    createSuppressiveSurround();
}

