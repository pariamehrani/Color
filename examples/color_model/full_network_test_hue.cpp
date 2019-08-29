#include "gtest/gtest.h"
#include <tarzann/ComputeStrategy.h>
#include <tarzann/Debug.h>
#include <tarzann/PLattice.h>
#include <tarzann/Probe.h>
#include <tarzann_gui/PLatticeGUI.h>
#include <fstream>
#include <sstream>
#include <time.h>


using namespace tarzann;
using namespace std;

void createSheets(PLattice* lattice,
                  std::string layer_name,
                  int scales,
                  int orientations,
                  int width,
                  int height,
                  NeuronType neuron_type)
{
    std::string sheet_name;

    for (int s=0; s<scales; s++)
    {
        for (int o=0; o<orientations; o++)
        {
            sheet_name = layer_name + "_" +std::to_string(s) + "_" + std::to_string(o);
            lattice->createSheet(layer_name,sheet_name,width,height,neuron_type);
        }
    }
}

void createSheets(PLattice* lattice,
                  std::string layer_name,
                  int num_sheets,
                  int width,
                  int height,
                  NeuronType neuron_type)
{
    std::string sheet_name;

    for (int s=0; s<num_sheets; s++)
    {
        sheet_name = layer_name + "_" +std::to_string(s) ;

        lattice->createSheet(layer_name,sheet_name,width,height,neuron_type);
    }
}

// Connect V2 neurons to a single V4 cell
void connectV2V4_Hue(PLattice* lattice,
                     std::string src_layer,
                     std::string src_sheet[], // an array of V2 sheet names
                     std::string dst_layer,
                     std::string dst_sheet,
                     float* weights, // an array of V2-V4 weights
                     std::string size,
                     std::string std,
                     int num_V2_sheets)
{
    std::map<std::string,std::string> FilterParameters;

    for(int i = 1; i < num_V2_sheets; i++) // Should be i = 0?
    {
        std::string conn = src_layer + "_" + dst_layer + "_"+ src_sheet[i]+ "_"+ dst_sheet;
        Connection* connection = lattice->createConnection(src_layer,src_sheet[i],
                                                           dst_layer, dst_sheet,
                                                           conn);

        //define the filter
        FilterParameters.clear();

        //global parameters
        FilterParameters["height"]=size;
        FilterParameters["width"]=size;
        FilterParameters["orientation"]="0";
        FilterParameters["fltr_Type"]="gauss";
        FilterParameters["shiftX"]="0";
        FilterParameters["shiftY"]="0";
        //gauss type parameters
        FilterParameters["sigma_x"]=std;
        FilterParameters["sigma_y"]=std;

        FilterParameters["weight"]=std::to_string(weights[i]);

        //add the filter
        if(connection != nullptr)
        {
            connection->addFilter(&FilterParameters);
        }
    }
}

// Modulatory (multiplicative) connection from V1 to V2
void connectV1V2_multiplicative_Hue(PLattice* lattice,
                                    std::string src_layer,
                                    std::string src_sheet1,
                                    std::string src_sheet2,
                                    std::string dst_layer,
                                    std::string dst_sheet,
                                    std::string size,
                                    std::string std)
{
    float weight = 1.0;

    // input to V2 from X_on channel
    std::map<std::string,std::string> FilterParameters;

    std::string conn = src_layer + "_" +dst_layer+ "_"+ src_sheet1+ "_"+ dst_sheet;
    Connection* connection = lattice->createConnection(src_layer,src_sheet1,
                                                       dst_layer, dst_sheet,
                                                       conn);


    //define the filter
    FilterParameters.clear();

    //global parameters
    FilterParameters["height"]=size;
    FilterParameters["width"]=size;
    FilterParameters["orientation"]="0";
    FilterParameters["fltr_Type"]="gauss";
    FilterParameters["shiftX"]="0";
    FilterParameters["shiftY"]="0";
    FilterParameters["weight"]=std::to_string( weight ) ;


    //gauss type parameters
    FilterParameters["sigma_x"]=std;
    FilterParameters["sigma_y"]=std;

    //add the filter
    if(connection != nullptr)
    {
        connection->addFilter(&FilterParameters);
    }

    // input to V2 from X_off channel
    std::string conn2 = src_layer + "_" +dst_layer+ "_"+ src_sheet2+ "_"+ dst_sheet;
    Connection* connection2 = lattice->createConnection(src_layer,src_sheet2,
                                                        dst_layer, dst_sheet,
                                                        conn2);


    //define the filter
    FilterParameters.clear();

    //global parameters
    FilterParameters["height"]=size;
    FilterParameters["width"]=size;
    FilterParameters["orientation"]="0";
    FilterParameters["fltr_Type"]="gauss";
    FilterParameters["shiftX"]="0";
    FilterParameters["shiftY"]="0";
    FilterParameters["weight"]=std::to_string( weight ) ;


    //gauss type parameters
    FilterParameters["sigma_x"]=std;
    FilterParameters["sigma_y"]=std;

    //add the filter
    if(connection2 != nullptr)
    {
        connection2->addFilter(&FilterParameters);
    }
}


void connectCones2LGN(PLattice* lattice,
                      std::string src_layer,
                      std::string dst_layer,
                      std::string dst_sheet,
                      float ConeWeight_L,
                      float ConeWeight_M,
                      float ConeWeight_S,
                      float RF_L,
                      float RF_M,
                      float RF_S)
{

    //create RF with filters
    int Ker_size = (int)max(max(RF_L,RF_M)  , RF_S );
    // make sure the kernel has odd width an height
    if(Ker_size % 2 == 0)
        Ker_size += 1;

    std::map<std::string,std::string> FilterParameters;
    std::string src_sheet = "RED";

    std::string conn = src_layer + "_" +dst_layer+ "_"+ src_sheet+ "_"+ dst_sheet;
    Connection* connection = lattice->createConnection(src_layer,src_sheet,
                                                       dst_layer, dst_sheet,
                                                       conn);


    //define the filter
    FilterParameters.clear();

    //global parameters
    FilterParameters["height"]=std::to_string( Ker_size) ;
    FilterParameters["width"]=std::to_string( Ker_size) ;
    FilterParameters["orientation"]="0";
    FilterParameters["fltr_Type"]="gauss";
    FilterParameters["shiftX"]="0";
    FilterParameters["shiftY"]="0";
    FilterParameters["weight"]=std::to_string(ConeWeight_L) ;

    //gauss type parameters
    FilterParameters["sigma_x"]=to_string(RF_L);
    FilterParameters["sigma_y"]=to_string(RF_L);



    //add the filter
    if(connection != nullptr)
    {
        connection->addFilter(&FilterParameters);
    }


    // *******************************************************************************
    std::string src_sheet2 = "GREEN";
    std::string conn2 = src_layer+" "+src_sheet2 + "_" +dst_layer ;
    Connection* connection2 = lattice->createConnection(src_layer,src_sheet2,
                                                        dst_layer, dst_sheet,
                                                        conn2);

    //define the filter
    FilterParameters.clear();

    //global parameters
    FilterParameters["height"]=std::to_string( Ker_size) ;
    FilterParameters["width"]=std::to_string( Ker_size) ;
    FilterParameters["orientation"]="0";
    FilterParameters["fltr_Type"]="gauss";
    FilterParameters["shiftX"]="0";
    FilterParameters["shiftY"]="0";
    FilterParameters["weight"]=std::to_string(ConeWeight_M) ;

    //gauss type parameters
    FilterParameters["sigma_x"]=to_string(RF_M);
    FilterParameters["sigma_y"]=to_string(RF_M);

    //add the filter
    if(connection2 != nullptr){
        connection2->addFilter(&FilterParameters);
    }
    // ******************************************************************************************
    std::string src_sheet3 = "BLUE";
    std::string conn3 = src_layer+" "+src_sheet3 + "_" +dst_layer ;
    Connection* connection3 = lattice->createConnection(src_layer,src_sheet3,
                                                        dst_layer, dst_sheet,
                                                        conn3);


    //define the filter
    FilterParameters.clear();
    //global parameters
    FilterParameters["height"]=std::to_string( Ker_size) ;
    FilterParameters["width"]=std::to_string( Ker_size) ;
    FilterParameters["orientation"]="0";
    FilterParameters["fltr_Type"]="gauss";
    FilterParameters["shiftX"]="0";
    FilterParameters["shiftY"]="0";
    FilterParameters["weight"]=std::to_string(ConeWeight_S) ;

    //gauss type parameters
    FilterParameters["sigma_x"]=to_string(RF_S);
    FilterParameters["sigma_y"]=to_string(RF_S);

    //add the filter
    if(connection3 != nullptr){
        connection3->addFilter(&FilterParameters);
    }

}

// Connect LGN->V1 and V1->V2 for single-opponent cells
void connectLayers_Hue(PLattice* lattice,
                       std::string src_layer,
                       std::string src_sheet,
                       std::string dst_layer,
                       std::string dst_sheet,
                       std::string size,
                       std::string std)
{
    std::map<std::string,std::string> FilterParameters;
    std::string conn = src_layer +"_"+ src_sheet +"_" + dst_layer + "_" + dst_sheet;
    Connection* connection = lattice->createConnection(src_layer,src_sheet,
                                                       dst_layer, dst_sheet,
                                                       conn);

    //define the filter
    FilterParameters.clear();

    //global parameters
    FilterParameters["height"]= size ;
    FilterParameters["width"]= size ;
    FilterParameters["orientation"]="0";
    FilterParameters["fltr_Type"]="gauss";
    FilterParameters["shiftX"]="0";
    FilterParameters["shiftY"]="0";
    FilterParameters["weight"]="1.0";


    //gaussian type parameters
    FilterParameters["sigma_x"]= std ;
    FilterParameters["sigma_y"]= std ;

    //add the filter
    if(connection != nullptr)
        connection->addFilter(&FilterParameters);
}

// Connect LGN neurons to double-opponent V1 cells
void connectLGN2doubleOpponentV1_Hue(PLattice* lattice,
                     std::string src_layer,
                     std::string src_sheet[], // an array of LGN sheet names
                     std::string dst_layer,
                     std::string dst_sheet,
                     float* weights, // an array of LGN2doube-opponent weights
                     float* size, // an array of kernel sizes
                     float* std, // an array of kernel stds
                     int num_LGN_sheets)
{
    std::map<std::string,std::string> FilterParameters;

    for(int i = 0; i < num_LGN_sheets; i++)
    {
        std::string conn = src_layer + "_" + dst_layer + "_"+ src_sheet[i]+ "_"+ dst_sheet;
        Connection* connection = lattice->createConnection(src_layer,src_sheet[i],
                                                           dst_layer, dst_sheet,
                                                           conn);
        //define the filter
        FilterParameters.clear();

        //global parameters
        FilterParameters["height"]=std::to_string(size[i]);
        FilterParameters["width"]=std::to_string(size[i]);
        FilterParameters["orientation"]="0";
        FilterParameters["fltr_Type"]="gauss";
        FilterParameters["shiftX"]="0";
        FilterParameters["shiftY"]="0";
        //gauss type parameters
        FilterParameters["sigma_x"]=std::to_string(std[i]);
        FilterParameters["sigma_y"]=std::to_string(std[i]);

        FilterParameters["weight"]=std::to_string(weights[i]);

        //add the filter
        if(connection != nullptr)
        {
            connection->addFilter(&FilterParameters);
        }
    }
}
/******************** Auxilliary help functins ************/

// Write a sheet to a text file
void writeSheet2File(std::string filename, Matrix* mat)
{
    ofstream file;
    file.open(filename, ios::out);
    if(!file){
        cout<< "Error opening file! filename: "<<filename<<endl;
        cin.get();
        return;
    }
    else
        cout<<"File opened successfully! filename: "<<filename<<endl;

    int m_height = 256;
    int m_width = 256;
    double resp = 0;

    for(int i=0; i<m_height; i++)
    {
        for(int j=0; j<m_width; j++)
        {
            resp=(*mat)(j,i);
            file<<resp;
            if(j != m_width - 1)
                file<<", ";
        }
        file<<endl;
    }
    file.close();
}


// Read cone->LGN weights from file
// assuming 7 LGN neurons types including luminance
float** read_LGN_cone_weights(std::string filename)
{
    ifstream file(filename);
    if(!file)
    {
        cerr<< "Error opening file! filename: "<<filename<<endl;
        cin.get();
        exit(1);
    }

    float** weights;
    int num_LGN_cells = 7;
    weights = new float*[num_LGN_cells];
    int j = 0;
    std::string line;
    for(int i = 0; i < num_LGN_cells; i++){
        weights[i] = new float[3];
        getline(file, line);

        stringstream ss(line);
        std::string field;
        while(getline(ss, field, ','))
        {
            weights[i][j] = std::stof(field.c_str());
            j++;

        }
        j = 0;
    }
    return weights;

}

// Read V2->V4 weights from file
// assuming 14 and 6 neurons types for V2 and V4
float** read_V4_weights(std::string filename)
{
    int num_V4 = 6;
    int num_V2 = 14;
    ifstream file(filename);
    if(!file)
    {
        cerr<< "Error opening file! filename: "<<filename<<endl;
        cin.get();
        exit(1);
    }

    //double w;
    float** weights;
    weights = new float*[num_V4];
    int j = 0;
    std::string line;
    for(int i = 0; i < num_V4; i++){
        weights[i] = new float[num_V2];
        getline(file, line);

        stringstream ss(line);
        std::string field;
        while(getline(ss, field, ','))
        {
            weights[i][j] = std::stof(field.c_str());
            j++;

        }
        j = 0;

    }
    return weights;

}

//***********************************************************************************

//***********************************************************************************//

void testFullNetwork(int argc, char **argv)
{

    int width = 256;
    int height = 256;

    float RFsize = 6.78; // Total size of the TarzaNN VF
    float ppd = width/RFsize; // Pixels per degree of visual field

    NeuronType neuron_type = linear2_nrn;
    SheetType mul_sheet_type = mul_sheet;


    // Read stimulus
    Stimulus* stimulus = new Stimulus(width,height,false);
    std::string imageName = argv[1];

    stimulus->loadStimulus(imageName);

    //p-lattice
    PLattice* lattice = new PLattice(COLOUR_INPUT,width,height);

    std::string LGN_weights_filename = "LGN_weights.txt";
    float** LGN_weights = read_LGN_cone_weights(LGN_weights_filename);

    std::string V4_weights_filename = "V4_weights.txt";

    std::string save_path = "./results/";

    float** V4_weights = read_V4_weights(V4_weights_filename);

    //create layers
    lattice->createLayer("LGN", INTERMEDIATE_LAYER);
    lattice->createLayer("V1", INTERMEDIATE_LAYER);
    lattice->createLayer("V2", INTERMEDIATE_LAYER);
    lattice->createLayer("V4", INTERMEDIATE_LAYER);

    //create LGN sheets for Hue
    string LGN_ColSheetName[] = {"L_on", "M_on", "S_on", "L_off", "M_off",\
                                 "S_off", "Lum"};

    int num_LGN_sheets = sizeof(LGN_ColSheetName) / sizeof(LGN_ColSheetName[0]);
    for(int n = 0; n < num_LGN_sheets; n++)
        lattice->getLayer("LGN")->createSheet(LGN_ColSheetName[n], width, height, neuron_type);

    // Set LGN neurons
    std::vector<Sheet*> LGN_sheets;
    lattice->getSheets("LGN", LGN_sheets);

    // set LGN neurons parameters
    float max_RvG = 0.184463793426914;
    float min_RvG = -0.105537544593049;
    float max_BvY = 0.8; // experimentally set
    float min_BvY = -0.5; // experimentally set
    float max_Y = 0.4; // experimentally set
    float min_Y = -0.5; // experimentally set
    float RvG_slope = 1/(max_RvG-min_RvG);
    float RvG_baseline = -min_RvG/(max_RvG-min_RvG);
    float BvY_slope = 1/(max_BvY-min_BvY);
    float BvY_baseline = -min_BvY/(max_BvY-min_BvY);
    float Y_slope = 1 / (max_Y - min_Y);
    float Y_baseline = -min_Y / (max_Y - min_Y);

    NeuronLinear2* neuron1_LGN = (NeuronLinear2*) LGN_sheets[0]->getNeuron();
    neuron1_LGN->setParameters(-1.0, 1.0, RvG_slope, RvG_baseline);//L_on
    NeuronLinear2* neuron2_LGN = (NeuronLinear2*) LGN_sheets[1]->getNeuron();
    neuron2_LGN->setParameters(-1.0, 1.0, RvG_slope, RvG_baseline);//M_on
    NeuronLinear2* neuron3_LGN = (NeuronLinear2*) LGN_sheets[2]->getNeuron();
    neuron3_LGN->setParameters(-1.0, 1.0, BvY_slope, BvY_baseline);//S_on
    NeuronLinear2* neuron4_LGN = (NeuronLinear2*) LGN_sheets[3]->getNeuron();
    neuron4_LGN->setParameters(-1.0, 1.0, RvG_slope, RvG_baseline);//L_off
    NeuronLinear2* neuron5_LGN = (NeuronLinear2*) LGN_sheets[4]->getNeuron();
    neuron5_LGN->setParameters(-1.0, 1.0, RvG_slope, RvG_baseline);//M_off
    NeuronLinear2* neuron6_LGN = (NeuronLinear2*) LGN_sheets[5]->getNeuron();
    neuron6_LGN->setParameters(-1.0, 1.0, Y_slope, Y_baseline);//S_off
    NeuronLinear2* neuron7_LGN = (NeuronLinear2*) LGN_sheets[6]->getNeuron();//Luminance
    neuron7_LGN->setParameters(0.0, 1.0, 1.0, 0.0);

    // Connect input (cone activations) to LGN neurons
    float LGN_gain = 1.0/255.0;
    double LGN_RF[] = {ppd * .166,ppd * 0.5};
    connectCones2LGN(lattice,"INPUT_LAYER","LGN",LGN_ColSheetName[0],LGN_gain*LGN_weights[0][0],LGN_gain*LGN_weights[0][1],LGN_gain*LGN_weights[0][2],LGN_RF[0],LGN_RF[1],LGN_RF[1]);//L_on
    connectCones2LGN(lattice,"INPUT_LAYER","LGN",LGN_ColSheetName[1],LGN_gain*LGN_weights[1][0],LGN_gain*LGN_weights[1][1],LGN_gain*LGN_weights[1][2],LGN_RF[1],LGN_RF[0],LGN_RF[1]);//M_on
    connectCones2LGN(lattice,"INPUT_LAYER","LGN",LGN_ColSheetName[2],LGN_gain*LGN_weights[2][0],LGN_gain*LGN_weights[2][1],LGN_gain*LGN_weights[2][2],LGN_RF[1],LGN_RF[1],LGN_RF[0]);//S_on
    connectCones2LGN(lattice,"INPUT_LAYER","LGN",LGN_ColSheetName[3],LGN_gain*LGN_weights[3][0],LGN_gain*LGN_weights[3][1],LGN_gain*LGN_weights[3][2],LGN_RF[0],LGN_RF[1],LGN_RF[1]);//L_off
    connectCones2LGN(lattice,"INPUT_LAYER","LGN",LGN_ColSheetName[4],LGN_gain*LGN_weights[4][0],LGN_gain*LGN_weights[4][1],LGN_gain*LGN_weights[4][2],LGN_RF[1],LGN_RF[0],LGN_RF[1]);//M_off
    connectCones2LGN(lattice,"INPUT_LAYER","LGN",LGN_ColSheetName[5],LGN_gain*LGN_weights[5][0],LGN_gain*LGN_weights[5][1],LGN_gain*LGN_weights[5][2],LGN_RF[1],LGN_RF[1],LGN_RF[0]);//S_off
    connectCones2LGN(lattice,"INPUT_LAYER","LGN",LGN_ColSheetName[6],LGN_gain*LGN_weights[6][0],LGN_gain*LGN_weights[6][1],LGN_gain*LGN_weights[6][2],LGN_RF[0],LGN_RF[0],LGN_RF[0]);//Luminance

    // Create V1 sheets
    string V1_ColSheetName[] = {"L_on", "M_on", "S_on", "L_off", "M_off", "S_off", "Lum"};

    lattice->getLayer("V1")->createSheet(V1_ColSheetName[0] , width, height,neuron_type); //V1 L_on
    lattice->getLayer("V1")->createSheet(V1_ColSheetName[1] , width, height,neuron_type); //V1 M_on
    lattice->getLayer("V1")->createSheet(V1_ColSheetName[2] , width, height,neuron_type); //V1 S_on
    lattice->getLayer("V1")->createSheet(V1_ColSheetName[3] , width, height,neuron_type); //V1 L_off
    lattice->getLayer("V1")->createSheet(V1_ColSheetName[4] , width, height,neuron_type); //V1 M_off
    lattice->getLayer("V1")->createSheet(V1_ColSheetName[5] , width, height,neuron_type); //V1 S_off
    lattice->getLayer("V1")->createSheet(V1_ColSheetName[6] , width, height,neuron_type); //V1 Lum


    // Set V1 neurons paramenters
    std::vector<Sheet*> V1_sheets;
    lattice->getSheets("V1", V1_sheets);
    int num_V1_sheets = (int) V1_sheets.size();
    for(int s=0; s<num_V1_sheets; s++)
    {
        NeuronLinear2* neuron1 = (NeuronLinear2*) V1_sheets[s]->getNeuron();
        if(s == 3)
            neuron1->setParameters(0.0, 1.0, 1 / 0.715, 0.0); // Experimentally set for V1 L_off
        else
            neuron1->setParameters(0.0, 1.0, 1.0, 0.0);

    }

    // Create V2 sheets, additive and multiplicative
    string V2_ColSheetName[] = {"L_on", "M_on", "S_on", "L_off", "M_off", "S_off", \
                                "mul_L_on_S_on", "mul_L_on_S_off", "mul_M_on_S_on", \
                                "mul_M_on_S_off", "mul_L_off_S_on", "mul_M_off_S_on", \
                                "mul_L_off_S_off", "mul_M_off_S_off"};

    lattice->getLayer("V2")->createSheet(V2_ColSheetName[0] , width, height,neuron_type); //V2 L_on
    lattice->getLayer("V2")->createSheet(V2_ColSheetName[1] , width, height,neuron_type); //V2 M_on
    lattice->getLayer("V2")->createSheet(V2_ColSheetName[2] , width, height,neuron_type); //V2 S_on
    lattice->getLayer("V2")->createSheet(V2_ColSheetName[3] , width, height,neuron_type); //V2 L_off
    lattice->getLayer("V2")->createSheet(V2_ColSheetName[4] , width, height,neuron_type); //V2 M_off
    lattice->getLayer("V2")->createSheet(V2_ColSheetName[5] , width, height,neuron_type); //V2 S_off
    lattice->getLayer("V2")->createSheet(V2_ColSheetName[6] , width, height,neuron_type, mul_sheet_type); //V2 mul_L_on_S_on
    lattice->getLayer("V2")->createSheet(V2_ColSheetName[7] , width, height,neuron_type, mul_sheet_type); //V2 mul_L_on_S_off
    lattice->getLayer("V2")->createSheet(V2_ColSheetName[8] , width, height,neuron_type, mul_sheet_type); //V2 mul_M_on_S_on
    lattice->getLayer("V2")->createSheet(V2_ColSheetName[9] , width, height,neuron_type, mul_sheet_type); //V2 mul_M_on_S_off
    lattice->getLayer("V2")->createSheet(V2_ColSheetName[10] , width, height,neuron_type, mul_sheet_type); //V2 mul_L_off_S_on
    lattice->getLayer("V2")->createSheet(V2_ColSheetName[11] , width, height,neuron_type, mul_sheet_type); //V2 mul_M_off_S_on
    lattice->getLayer("V2")->createSheet(V2_ColSheetName[12] , width, height,neuron_type, mul_sheet_type); //V2 mul_L_off_S_off
    lattice->getLayer("V2")->createSheet(V2_ColSheetName[13] , width, height,neuron_type, mul_sheet_type); //V2 mul_M_off_S_off

    // Set V2 neurons parameters
    std::vector<Sheet*> V2_sheets;
    lattice->getSheets("V2", V2_sheets);
    int num_V2_sheets = (int) V2_sheets.size();
    int V2_identity_param_neurons[] = {0, 1, 2, 3, 4, 5, 7, 8};
    int V2_id_size = *(&V2_identity_param_neurons + 1) - V2_identity_param_neurons;
    for(int s=0; s<V2_id_size; s++)
    {
        NeuronLinear2* neuron2 = (NeuronLinear2*) V2_sheets[V2_identity_param_neurons[s]]->getNeuron();
        neuron2->setParameters(0.0, 1.0, 1.0, 0.0);
    }

    // Set the slope of some V2 neurons (NOTE: the slopes are set EXPERIMENTALLY)
    NeuronLinear2* neuron6 = (NeuronLinear2*) V2_sheets[6]->getNeuron();//mul_L_on_S_on
    neuron6->setParameters(0.0, 1.0, 1 / 0.664, 0.0);
    NeuronLinear2* neuron9 = (NeuronLinear2*) V2_sheets[9]->getNeuron();//mul_M_on_S_off
    neuron9->setParameters(0.0, 1.0, 1 / 0.731, 0.0);
    NeuronLinear2* neuron10 = (NeuronLinear2*) V2_sheets[10]->getNeuron();//mul_L_off_S_on
    neuron10->setParameters(0.0, 1.0, 1 / 0.652, 0.0);
    NeuronLinear2* neuron11 = (NeuronLinear2*) V2_sheets[11]->getNeuron();//mul_M_off_S_on
    neuron11->setParameters(0.0, 1.0, 1 / 0.426, 0.0);
    NeuronLinear2* neuron12 = (NeuronLinear2*) V2_sheets[12]->getNeuron();//mul_L_off_S_off
    neuron12->setParameters(0.0, 1.0, 1 /  0.5374, 0.0);
    NeuronLinear2* neuron13 = (NeuronLinear2*) V2_sheets[13]->getNeuron();//mul_M_off_S_off
    neuron13->setParameters(0.0, 1.0, 1 / 0.6570, 0.0);

    // Create V4 sheets
    string V4_ColSheetName[] = {"red", "yellow", "green", "cyan", "blue", "magenta"};
    lattice->getLayer("V4")->createSheet(V4_ColSheetName[0] , width, height,neuron_type);
    lattice->getLayer("V4")->createSheet(V4_ColSheetName[1] , width, height,neuron_type);
    lattice->getLayer("V4")->createSheet(V4_ColSheetName[2] , width, height,neuron_type);
    lattice->getLayer("V4")->createSheet(V4_ColSheetName[3] , width, height,neuron_type);
    lattice->getLayer("V4")->createSheet(V4_ColSheetName[4] , width, height,neuron_type);
    lattice->getLayer("V4")->createSheet(V4_ColSheetName[5] , width, height,neuron_type);

    // Set V4 neurons parameters
    std::vector<Sheet*> V4_sheets;
    lattice->getSheets("V4", V4_sheets);
    int num_V4_sheets = (int) V4_sheets.size();
    std::array<float, 6> V4_slope;

    // Slopes for the desired angles at 60deg apart in hsv--converted to MB angles
    V4_slope = {1.0 / 0.6047, 1.0 / 0.7169, 1.0 / 0.9345, 1.0 / 0.9620, \
                        1.0 / 0.9747, 1.0 / 0.8940};

    for(int s = 0; s < num_V4_sheets; s++)
    {
        NeuronLinear2* neuron4 = (NeuronLinear2*) V4_sheets[s]->getNeuron();
        neuron4->setParameters(0.0, 1.0, V4_slope[s], 0.0);
    }

    // Add connections
    std::string LGN2V1_filt_size=std::to_string(19); std::string LGN2V1_filt_std=std::to_string(ppd*8);
    connectLayers_Hue(lattice, "LGN",LGN_ColSheetName[0],"V1",V1_ColSheetName[0],LGN2V1_filt_size,LGN2V1_filt_std);
    connectLayers_Hue(lattice, "LGN",LGN_ColSheetName[1],"V1",V1_ColSheetName[1],LGN2V1_filt_size,LGN2V1_filt_std);
    connectLayers_Hue(lattice, "LGN",LGN_ColSheetName[2],"V1",V1_ColSheetName[2],LGN2V1_filt_size,LGN2V1_filt_std);
    connectLayers_Hue(lattice, "LGN",LGN_ColSheetName[3],"V1",V1_ColSheetName[3],LGN2V1_filt_size,LGN2V1_filt_std);
    connectLayers_Hue(lattice, "LGN",LGN_ColSheetName[4],"V1",V1_ColSheetName[4],LGN2V1_filt_size,LGN2V1_filt_std);
    connectLayers_Hue(lattice, "LGN",LGN_ColSheetName[5],"V1",V1_ColSheetName[5],LGN2V1_filt_size,LGN2V1_filt_std);
    connectLayers_Hue(lattice, "LGN",LGN_ColSheetName[6],"V1",V1_ColSheetName[6],LGN2V1_filt_size,LGN2V1_filt_std);

    std::string V12V2_filt_size=std::to_string(57); std::string V12V2_filt_std=std::to_string(ppd*2.6);
   
    // Connect the on&off single-opponent (SO) V1 cells to on&off SO V2 neurons
    for(int i = 0; i < 6; i++)
    {
        connectLayers_Hue(lattice, "V1", V1_ColSheetName[i], "V2", V2_ColSheetName[i],V12V2_filt_size,V12V2_filt_std);
    }

    connectV1V2_multiplicative_Hue(lattice, "V1", V1_ColSheetName[0], V1_ColSheetName[2], "V2",\
                              V2_ColSheetName[6], V12V2_filt_size, V12V2_filt_std); //mul_L_on_S_on
    connectV1V2_multiplicative_Hue(lattice, "V1", V1_ColSheetName[0], V1_ColSheetName[5], "V2",\
                              V2_ColSheetName[7], V12V2_filt_size, V12V2_filt_std);  //mul_L_on_S_off
    connectV1V2_multiplicative_Hue(lattice, "V1", V1_ColSheetName[1], V1_ColSheetName[2], "V2",\
                              V2_ColSheetName[8], V12V2_filt_size, V12V2_filt_std);  //mul_M_on_S_on
    connectV1V2_multiplicative_Hue(lattice, "V1", V1_ColSheetName[1], V1_ColSheetName[5], "V2",\
                              V2_ColSheetName[9], V12V2_filt_size, V12V2_filt_std);  //mul_M_on_S_off
    connectV1V2_multiplicative_Hue(lattice, "V1", V1_ColSheetName[3], V1_ColSheetName[2], "V2",\
                              V2_ColSheetName[10], V12V2_filt_size, V12V2_filt_std);  //mul_L_off_S_on
    connectV1V2_multiplicative_Hue(lattice, "V1", V1_ColSheetName[4], V1_ColSheetName[2], "V2",\
                              V2_ColSheetName[11], V12V2_filt_size, V12V2_filt_std);  //mul_M_off_S_on
    connectV1V2_multiplicative_Hue(lattice, "V1", V1_ColSheetName[3], V1_ColSheetName[5], "V2",\
                              V2_ColSheetName[12], V12V2_filt_size, V12V2_filt_std);  //mul_L_off_S_off
    connectV1V2_multiplicative_Hue(lattice, "V1", V1_ColSheetName[4], V1_ColSheetName[5], "V2",\
                              V2_ColSheetName[13], V12V2_filt_size, V12V2_filt_std);  //mul_M_off_S_off


    std::string V2V4_filt_size=std::to_string(67); std::string V2V4_filt_std=std::to_string(ppd*2.6);
    for(int i = 0; i < num_V4_sheets; i++)
    {
        connectV2V4_Hue(lattice, "V2", V2_ColSheetName, "V4", V4_ColSheetName[i], V4_weights[i], V2V4_filt_size,V2V4_filt_std, num_V2_sheets);
    }


    //create a compute strategy
    ComputeStrategy* compute_strategy = new ComputeStrategy(TASK_LOCALIZATION,
                                                            100,
                                                            lattice);

    for(int i=0; i<1; i++)
    {

        if(i==0)
            lattice->presentStimulus(stimulus);

        compute_strategy->run();
    }

    cout<<"Done with computation."<<endl;
    std::size_t found = imageName.find_last_of("/");
    std::size_t founddot = imageName.find_last_of(".");
    std::string imgNameNoPath = imageName.substr(found + 1, founddot - found - 1);


    // Write V4 activities
    for(int n = 0; n < num_V4_sheets; n++)
    {
        std::string V4_fileName = save_path + imgNameNoPath + "_V4_" + \
                V4_ColSheetName[n] + "_sheet.txt";
        Sheet* V4_sheet = lattice->getSheet("V4", V4_ColSheetName[n]);
        Matrix* V4_activation = V4_sheet->getOutput();
        writeSheet2File(V4_fileName, V4_activation);
    }

    return;
}


int main(int argc, char **argv)
{

    testFullNetwork(argc, argv);

}
