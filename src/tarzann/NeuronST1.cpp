#include <tarzann/Debug.h>
#include<tarzann/NeuronST1.h>

using namespace std;
using namespace tarzann;


NeuronST1::NeuronST1(Sheet* sheet) : Neuron(sheet)
{
    //integration time step (s)
    m_t_step=0.0025;

    //this is the slope of the sigmoid function usually 3 for retinal cells
    m_exponent=3.0;

    // maximum firing rate of the neurons in the visual cortex
    //set to 100 by defaoult in the STNeuron.h header
    m_max_activation=1.0;

     //point of half activation of the sigmoid function
    m_sigma=0.45* m_max_activation;//*m_max_activation;

    //realistic decay time for inhibition: tau~10ms
    m_tau_0=0.011;


    //time ratio used for the final computation of dxdt
    m_one_over_tau=1.0/m_tau_0;

    //ih parameters
    m_inv_ih_tau_fast=1.0/0.05;
    m_inv_ih_tau_slow=1.0/0.9;
    m_max_ih_slow=2.0;
    m_max_ih_fast=1.3;

   //necessary constant for the Runge-Kutta algorithm
    m_t_step_sixths=m_t_step*0.166667;

    m_conlv_ffwd_inputs=sheet->getConvolvedInputs();

    m_sheet_activ=sheet->getOutput();

    m_h_curr=sheet->getH_currs();

    m_spatial_bias=sheet->getSpatialBias();

    m_feature_bias=sheet->getFeatureBias();

    m_width=sheet->getOutput()->getXSize();

    m_height=sheet->getOutput()->getYSize();

    resetHcurrs();

}

void NeuronST1::ComputeCoefficientsForRungeKutta4(
                float current_state,
                H_curr current_ih,
                float convl_ins,
                float F_x0,
                H_curr Ih_0,
                float spatial_bias,
                float feature_bias,
                float *K, float *ih_s,
                float *ih_f){


    H_curr new_ih;

    //First RK coeff

    ih_s[0]=Ih_0.h_slow;
    ih_f[0]=Ih_0.h_fast;
    K[0]=F_x0;


    //2nd RK coeff
    new_ih.h_slow=current_ih.h_slow+0.5*m_t_step*ih_s[0];
    new_ih.h_fast=current_ih.h_fast+0.5*m_t_step*ih_f[0];
    float new_activation=current_state+0.5*m_t_step*K[0];

    ih_s[1]=evaluateH(new_activation,new_ih).h_slow;
    ih_f[1]=evaluateH(new_activation,new_ih).h_fast;
    K[1]=EvaluateSTunFunctionWith(new_activation,new_ih,convl_ins,
                                  spatial_bias,feature_bias);


    //3rd RK coeff
    new_ih.h_slow=current_ih.h_slow+0.5*m_t_step*ih_s[1];
    new_ih.h_fast=current_ih.h_fast+0.5*m_t_step*ih_f[1];
    new_activation=current_state+0.5*m_t_step*K[1];


    ih_s[2]=evaluateH(new_activation,new_ih).h_slow;
    ih_f[2]=evaluateH(new_activation,new_ih).h_fast;
    K[2]=EvaluateSTunFunctionWith(new_activation,current_ih,convl_ins,
                                  spatial_bias,feature_bias);




    //4th RK coeff
    new_ih.h_slow=current_ih.h_slow+m_t_step*ih_s[2];
    new_ih.h_fast=current_ih.h_fast+m_t_step*ih_f[2];
    new_activation=current_state+m_t_step*K[2];

    ih_s[3]=evaluateH(new_activation,new_ih).h_slow;
    ih_f[3]=evaluateH(new_activation,new_ih).h_fast;
    K[3]=EvaluateSTunFunctionWith(new_activation,current_ih,convl_ins,
                                  spatial_bias,feature_bias);


}



H_curr NeuronST1::evaluateH(float current_activation, H_curr Ih){

    H_curr ih;
    ih.h_fast=m_inv_ih_tau_fast*(-Ih.h_fast+current_activation);
    ih.h_slow=m_inv_ih_tau_slow*(-Ih.h_slow+current_activation);

    return ih;
}




float NeuronST1::evaluateSigma(H_curr ih){

    float sigma;
    sigma=m_sigma+m_max_ih_fast*ih.h_fast+m_max_ih_slow*ih.h_slow;

    return sigma;
}


float NeuronST1::EvaluateSTunFunctionWith(float current_activation,
                                         H_curr current_ih,
                                         float cnvl_input,
                                         float spatial_bias,
                                         float feature_bias)
{

    float sigma;
    sigma=evaluateSigma(current_ih);

    float sigmoid=m_max_activation*pow(cnvl_input,m_exponent)/
            ((pow(sigma,m_exponent))+pow(cnvl_input,m_exponent));

    float F_x=m_one_over_tau*(-current_activation+
                         std::min(spatial_bias,feature_bias)*sigmoid);

    return F_x;
}




void NeuronST1::ComputeActivation(uint32_t global_time)
{
    tarzannDebug("ComputeActivation");
    //actual units of time (s)" (to be used in the probe class)
    m_current_Global_time=(float)m_t_step*global_time;
    m_spatial_bias = m_sheet->getSpatialBias();
    m_feature_bias = m_sheet->getFeatureBias();

    float current_activ=0.0;
    H_curr current_i;

    float convl_in=0.0;
    float *curr_activ;
    float *curr_ih_slow;
    float *curr_ih_fast;
    float spatial_bias=0.0;
    float K_vect[4]={0};
    float H_slow[4]={0};
    float H_fast[4]={0};

    //F_x will hold the function representing time-evolution of the Neuron_ST
    float F_x0=0.0;
    H_curr IH_0;

    for(uint32_t i=0;i<m_width; i++)
        for(uint32_t j=0; j<m_height; j++){

            //current response
            curr_activ=&(*m_sheet_activ)(i,j);
            current_activ=(*m_sheet_activ)(i,j);

            //current Ih fast component
            curr_ih_fast=&(*m_h_curr)(i,j).h_fast;
            current_i.h_fast=(*m_h_curr)(i,j).h_fast;


            //current Ih slow component
            curr_ih_slow=&(*m_h_curr)(i,j).h_slow;
            current_i.h_slow=(*m_h_curr)(i,j).h_slow;


            convl_in=(*m_conlv_ffwd_inputs)(i,j);

            //the cell receives either 0 or more than  0 spikes
            convl_in=(convl_in+fabs(convl_in))*0.5;

            spatial_bias= (*m_spatial_bias)(i,j);

            IH_0.h_slow=evaluateH(current_activ,current_i).h_slow;
            IH_0.h_fast=evaluateH(current_activ,current_i).h_fast;

            F_x0=EvaluateSTunFunctionWith(current_activ,current_i,convl_in,
                                          spatial_bias,
                                          m_feature_bias);

            ComputeCoefficientsForRungeKutta4(current_activ,
                                              current_i,
                                              convl_in,F_x0,
                                              IH_0,
                                              spatial_bias,
                                              m_feature_bias, K_vect,
                                              H_slow,H_fast);

            SolveEqUsingRK4andUpdate(curr_ih_slow,
                                    m_current_Global_time,
                                    m_t_step,
                                    m_t_step_sixths,
                                    H_slow);

            SolveEqUsingRK4andUpdate(curr_ih_fast,
                                    m_current_Global_time,
                                    m_t_step,
                                    m_t_step_sixths,
                                    H_fast);

            SolveEqUsingRK4andUpdate(curr_activ,
                                    m_current_Global_time,
                                    m_t_step,
                                    m_t_step_sixths,
                                    K_vect);

        }
}



void NeuronST1::resetHcurrs(){

    for(uint32_t i=0;i<m_width;i++){
        for(uint32_t j=0;j<m_height;j++){
            (*m_h_curr)(i,j).h_fast=0.0;
            (*m_h_curr)(i,j).h_slow=0.0;
        }
    }

}


NeuronST1::~NeuronST1(){

}


