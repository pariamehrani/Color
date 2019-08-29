#include<tarzann/NeuronLinear.h>

using namespace tarzann;

NeuronLinear::NeuronLinear(Sheet* sheet): Neuron(sheet)
{
    m_width=sheet->getOutput()->getXSize();

    m_height=sheet->getOutput()->getYSize();

    m_sheet_activ=sheet->getOutput();

    m_convl_ffwd_inputs = sheet->getConvolvedInputs();
    //cout << "neuron test1: "<< sheet<<endl;
}


void NeuronLinear::ComputeActivation(uint32_t global_time)
{
    //cout<< "neuron linear: compute activation"<< endl;

    float *curr_activ;
    //float current_activation=0.0;
    //float base_spikerate=0.5;
    float convl_in=0.0;
    float new_activation=0.0;

    for(uint32_t i=0;i<m_width; i++)
       for(uint32_t j=0; j<m_height; j++){
           curr_activ=&(*m_sheet_activ)(i,j);
           //current_activation=(*m_sheet_activ)(i,j);
           convl_in=(*m_convl_ffwd_inputs)(i,j);

           if(convl_in>=m_threshold)
           {

               //new_activation=0.5*convl_in+base_spikerate;
                 //new_activation = 2*(convl_in-min)/(max-min);
                new_activation=0.5;
               if(new_activation<=m_satur_rate){
                   *curr_activ=new_activation;
               }
               else if(new_activation>m_satur_rate){
                   *curr_activ=1;


               }
           }else{
               *curr_activ=0;
           }

       }
}

NeuronLinear::~NeuronLinear()
{

}
