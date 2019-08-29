//#ifndef _NEURON_linear2_H_
//#define _NEURON_linear2_H_
//#include<tarzann/Neuron.h>
//#include<tarzann/Sheet.h>
//#include<tarzann/Matrix.h>

//namespace tarzann{
//class Sheet;

//class NeuronLinear2:public Neuron{


//public:
//    NeuronLinear2(Sheet* sheet);
//    ~NeuronLinear2();
//    virtual void ComputeActivation(uint32_t global_time);

//protected:
//    Matrix* m_sheet_activ;
//    Matrix* m_convl_ffwd_inputs;
//    float m_threshold=0;//non or all activation threshold
//    float m_satur_rate=1;

//    uint32_t m_width, m_height;
//};

//}
//#endif

#ifndef _NEURON_linear2_H_
#define _NEURON_linear2_H_
#include<tarzann/Neuron.h>
#include<tarzann/Sheet.h>
#include<tarzann/Matrix.h>

namespace tarzann{
class Sheet;

class NeuronLinear2:public Neuron{


public:
    NeuronLinear2(Sheet* sheet);
    ~NeuronLinear2();
    virtual void ComputeActivation(uint32_t global_time);
    void setParameters(float threshold,
                       float saturation,
                       float slope,
                       float base_spike_rate);

protected:
    Matrix* m_sheet_activ;
    Matrix* m_convl_ffwd_inputs;
    float m_threshold;
    float m_saturation;
    float m_slope;
    float m_base_spike_rate;
    uint32_t m_width;
    uint32_t m_height;
};

}
#endif
