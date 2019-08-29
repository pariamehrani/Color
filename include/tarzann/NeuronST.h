#ifndef NEURON_ST_H
#define NEURON_ST_H

#include <tarzann/Neuron.h>
#include<tarzann/Sheet.h>
#include<tarzann/Matrix.h>


namespace tarzann {

class Sheet;
class Matrix;

class NeuronST:public Neuron{

public:
    NeuronST(Sheet *sheet);

    ~NeuronST();

    float EvaluateSTunFunctionWith(float current_activation,
                                   float cnvl_input,
                                   float spatial_bias,
                                   float feature_bias);


    virtual void ComputeActivation(uint32_t global_time);

    void ComputeCoefficientsForRungeKutta4(float current_activation,
                                            float convl_ins,
                                            float F_x0,
                                            float current_time,
                                            float time_step,
                                            float spatial_bias,
                                            float feature_bias,
                                            float* K);
    float getMaxActivST();
    float getSigmaST();
    float getExponST();

protected:
    uint32_t m_width, m_height;

    float m_feature_bias;
    Matrix* m_conlv_ffwd_inputs;
    Matrix* m_sheet_activ;
    Matrix* m_spatial_bias;

    float m_current_Global_time;
    float m_exponent;
    float m_max_activation;
    float m_sigma;
    float m_tau_0;
    float m_t_step;
    float m_one_over_tau;
    float m_t_step_sixths;
};

}
#endif
