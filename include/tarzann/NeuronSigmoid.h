#ifndef _NEURON_Sigmoid_H_
#define _NEURON_Sigmoid_H_
#include<tarzann/Neuron.h>
#include<tarzann/Sheet.h>
#include<tarzann/Matrix.h>

namespace tarzann{

class Sheet;
class Matrix;

class NeuronSigmoid:public Neuron
{

public:
    NeuronSigmoid(Sheet *sheet);
    ~NeuronSigmoid();
    float EvaluateSigmoidFunctionWith(float current_activation,
                                      float shift,
                                      float max_activation,
                                      float slope,
                                      float spatial_bias,
                                      float feature_bias);

    virtual void ComputeActivation(uint32_t global_time);


    float getMaxActiv();




protected:
    float m_feature_bias;
    Matrix* m_conlv_ffwd_inputs;
    Matrix* m_sheet_activ;
    Matrix* m_spatial_bias;
    float m_current_Global_time;
    float m_t_step;
    float m_shift=0.0f;
    float m_max_activation=1.0f;
    float m_slope=0.5f;
    uint32_t m_width, m_height;



};


}
#endif
