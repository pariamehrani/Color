/**
 * @brief   This class computes the temporal evolution
 *          of the ST Neuron following Tsotsos book diff eq.
 *          including h-currents to modulate the half saturation constant
 * @author  Oscar J. Avella-Gonzalez
 * @date    June 7, 2016
 */

#ifndef NEURON_ST1_H
#define NEURON_ST1_H


#include<iostream>
#include <string>
#include <math.h>
#include <tarzann/Neuron.h>
#include<tarzann/Sheet.h>
#include<tarzann/Matrix.h>


namespace tarzann {

class Sheet;
class Matrix;

class NeuronST1:public Neuron{

public:
    NeuronST1(Sheet* sheet);
    ~NeuronST1();

    float EvaluateSTunFunctionWith(float current_activation,
                                   H_curr current_ih,
                                   float cnvl_input,
                                   float spatial_bias,
                                   float feature_bias);


    H_curr evaluateH(float current_activation, H_curr ih);
    float evaluateSigma(H_curr ih);


    virtual void ComputeActivation(uint32_t global_time);

    void ComputeCoefficientsForRungeKutta4(float current_state,
                                           H_curr current_ih,
                                           float convl_ins,
                                           float F_x0,
                                           H_curr Ih_0,
                                           float spatial_bias,
                                           float feature_bias,
                                           float* K, float *ih_s,
                                           float *ih_f);
    void resetHcurrs();



protected:

    uint32_t m_width, m_height;

    float m_feature_bias;
    Matrix* m_conlv_ffwd_inputs;
    Matrix* m_sheet_activ;
    Array2D<H_curr>* m_h_curr;
    Matrix* m_spatial_bias;

    float m_current_Global_time;
    float m_exponent;
    float m_max_activation;
    float m_sigma;
    float m_tau_0;

    //ih parameters
    float m_max_ih_slow;
    float m_max_ih_fast;
    float m_inv_ih_tau_slow;
    float m_inv_ih_tau_fast;

    float m_t_step;
    float m_one_over_tau;
    float m_t_step_sixths;

};

}

#endif
