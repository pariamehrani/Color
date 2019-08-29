#include <math.h>
#include <string>

#include <tarzann/Debug.h>
#include <tarzann/NeuronST.h>

using namespace tarzann;

NeuronST::NeuronST(Sheet* sheet):Neuron(sheet)
{
    //integration time step (s)
    m_t_step=0.0025;

    //this is the slope of the sigmoid function usually 3 for retinal cells
    m_exponent=3.0;

    // maximum firing rate of the neurons in the visual cortex
    //set to 100 by defaoult in the STNeuron.h header
    m_max_activation=1.0;

     //point of half activation of the sigmoid function
    m_sigma=0.5*m_max_activation;

    //realistic decay time for inhibition: tau~10ms
    m_tau_0=0.011;


    //time ratio used for the final computation of dxdt
    m_one_over_tau=1.0/m_tau_0;

   //necessary constant for the Runge-Kutta algorithm
    m_t_step_sixths=m_t_step*0.166667;

    m_conlv_ffwd_inputs=sheet->getConvolvedInputs();

    m_sheet_activ=sheet->getOutput();

    m_spatial_bias=sheet->getSpatialBias();

    m_feature_bias=sheet->getFeatureBias();

    m_width=sheet->getOutput()->getXSize();

    m_height=sheet->getOutput()->getYSize();


}


void NeuronST::ComputeCoefficientsForRungeKutta4(
                float current_activation,
                float convl_ins,
                float F_x0,
                float current_time,
                float time_step,
                float spatial_bias,
                float feature_bias,
                float *K){
    //First RK coeff
    K[0]=F_x0;
    float new_activation=current_activation+0.5*m_t_step*K[0];


    //2nd RK coeff
    K[1]=EvaluateSTunFunctionWith(new_activation,convl_ins,
                                  spatial_bias,feature_bias);



    new_activation=current_activation+0.5*m_t_step*K[1];


    //3rd RK coeff
    K[2]=EvaluateSTunFunctionWith(new_activation,convl_ins,
                                  spatial_bias,feature_bias);



    new_activation=current_activation+m_t_step*K[2];

    //4th RK coeff
    K[3]=EvaluateSTunFunctionWith(new_activation,convl_ins,
                                  spatial_bias,feature_bias);


}



float NeuronST::EvaluateSTunFunctionWith(float current_activation,
                                         float cnvl_input,
                                         float spatial_bias,
                                         float feature_bias)
{

    float sigmoid=m_max_activation*pow(cnvl_input,m_exponent)/
            ((pow(m_sigma,m_exponent))+pow(cnvl_input,m_exponent));

    float F_x=m_one_over_tau*(-current_activation+
                         std::min(spatial_bias,feature_bias)*sigmoid);

    return F_x;
}

void NeuronST::ComputeActivation(uint32_t global_time)
{
    m_spatial_bias = m_sheet->getSpatialBias();
    m_feature_bias = m_sheet->getFeatureBias();

    tarzannDebug("ComputeActivation");
    //actual units of time (s)" (to be used in the probe class)
    m_current_Global_time=(float)m_t_step*global_time;

    float current_activation=0.0;
    float convl_in=0.0;
    float *curr_activ;
    float spatial_bias=0.0;
    float K_vect[4]={0};

    //F_x will hold the function representing time-evolution of the Neuron_ST
    float F_x0=0.0;

    for(uint32_t i=0;i<m_width; i++)
        for(uint32_t j=0; j<m_height; j++){

            curr_activ=&(*m_sheet_activ)(i,j);

            current_activation=(*m_sheet_activ)(i,j);

            convl_in=(*m_conlv_ffwd_inputs)(i,j);

            //the cell receives either 0 or more than  0 spikes
            convl_in=(convl_in+fabs(convl_in))*0.5;

            spatial_bias= (*m_spatial_bias)(i,j);

            F_x0=EvaluateSTunFunctionWith(current_activation,convl_in,
                                          spatial_bias,
                                          m_feature_bias);

            ComputeCoefficientsForRungeKutta4(current_activation,
                                              convl_in,F_x0,
                                              m_current_Global_time,
                                              m_t_step,spatial_bias,
                                              m_feature_bias, K_vect);

            SolveEqUsingRK4andUpdate(curr_activ,
                                    m_current_Global_time,
                                    m_t_step,
                                    m_t_step_sixths,
                                    K_vect);

        }
}

float NeuronST::getMaxActivST()
{
    return m_max_activation;
}

float NeuronST::getSigmaST()
{
    return m_sigma;
}

float NeuronST::getExponST()
{
    return m_exponent;
}

NeuronST::~NeuronST()
{

}
