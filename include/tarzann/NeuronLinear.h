#ifndef _NEURON_linear_H_
#define _NEURON_linear_H_
#include<tarzann/Neuron.h>
#include<tarzann/Sheet.h>
#include<tarzann/Matrix.h>

namespace tarzann{
class Sheet;

class NeuronLinear:public Neuron{


public:
    NeuronLinear(Sheet* sheet);
    ~NeuronLinear();
    virtual void ComputeActivation(uint32_t global_time);

protected:
    Matrix* m_sheet_activ;
    Matrix* m_convl_ffwd_inputs;
    float m_threshold=-1;//non or all activation threshold
    float m_satur_rate=1;

    uint32_t m_width, m_height;

};

}
#endif
