//#include<tarzann/NeuronLinear2.h>

//using namespace tarzann;

//NeuronLinear2::NeuronLinear2(Sheet* sheet): Neuron(sheet)
//{
//    m_width=sheet->getOutput()->getXSize();

//    m_height=sheet->getOutput()->getYSize();

//    m_sheet_activ=sheet->getOutput();

//    m_convl_ffwd_inputs = sheet->getConvolvedInputs();
//}


//void NeuronLinear2::ComputeActivation(uint32_t global_time)

//{
//    //cout<< "neuron linear: compute activation"<< endl;

//    float *curr_activ;
//    float current_activation=0.0;
//    float base_spikerate=0;
//    float convl_in=0.0;
//    float new_activation=0.0;

//    for(uint32_t i=0;i<m_width; i++)
//       for(uint32_t j=0; j<m_height; j++){
//           curr_activ=&(*m_sheet_activ)(i,j);
//           current_activation=(*m_sheet_activ)(i,j);
//           convl_in=(*m_convl_ffwd_inputs)(i,j);

//           if(convl_in>=m_threshold)
//           {
//               //new_activation=current_activation+convl_in;


//               new_activation=convl_in+base_spikerate;

//               if(new_activation<=m_satur_rate){
//                   *curr_activ=new_activation;
//               }
//               else if(new_activation>m_satur_rate){
//                   *curr_activ=m_satur_rate;


//               }
//           }else{
//               *curr_activ=0;
//           }

//       }
//}

//NeuronLinear2::~NeuronLinear2()
//{

//}

#include<tarzann/NeuronLinear2.h>

using namespace tarzann;

NeuronLinear2::NeuronLinear2(Sheet* sheet): Neuron(sheet)
{
    m_width=sheet->getOutput()->getXSize();

    m_height=sheet->getOutput()->getYSize();

    m_sheet_activ=sheet->getOutput();

    m_convl_ffwd_inputs = sheet->getConvolvedInputs();
}

void NeuronLinear2::setParameters(float threshold,
                                  float saturation,
                                  float slope,
                                  float base_spike_rate)
{
    m_threshold = threshold;
    m_saturation = saturation;
    m_slope = slope;
    m_base_spike_rate = base_spike_rate;
}

void NeuronLinear2::ComputeActivation(uint32_t global_time)
{
    float *curr_activ;
    float current_activation=0.0;
    float convl_in = 0.0;
    float new_activation=0.0;

    for(uint32_t i=0;i<m_width; i++){
       for(uint32_t j=0; j<m_height; j++){
           curr_activ=&(*m_sheet_activ)(i,j);
           current_activation=(*m_sheet_activ)(i,j);
           convl_in=(*m_convl_ffwd_inputs)(i,j);

            //*curr_activ =  1.0;
           if(current_activation >= m_threshold)
           {
               new_activation=m_slope*convl_in+m_base_spike_rate;

                              if(new_activation<=m_saturation){
                                  *curr_activ=new_activation;
                              }
                              else if(new_activation>m_saturation){
                                  *curr_activ=m_saturation;
                              }

                              if(new_activation<m_threshold){
                                  *curr_activ=m_threshold;
                              }

           }else{
               *curr_activ=m_threshold;
           }


       }
    }
}
NeuronLinear2::~NeuronLinear2()
{

}
