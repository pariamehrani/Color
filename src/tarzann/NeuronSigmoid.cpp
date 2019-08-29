#include<tarzann/NeuronSigmoid.h>
#include<math.h>
using namespace tarzann;

NeuronSigmoid::NeuronSigmoid(Sheet* sheet):Neuron(sheet)
{
    m_conlv_ffwd_inputs=sheet->getConvolvedInputs();

    m_sheet_activ=sheet->getOutput();

    m_spatial_bias=sheet->getSpatialBias();

    m_feature_bias=sheet->getFeatureBias();

    m_width=sheet->getOutput()->getXSize();

    m_height=sheet->getOutput()->getYSize();

}
NeuronSigmoid::~NeuronSigmoid(){}



float NeuronSigmoid::EvaluateSigmoidFunctionWith(float current_activation,
                               float shift,
                               float max_activation,
                               float slope,
                               float spatial_bias,
                               float feature_bias)
{
    float sigmoid=max_activation/(1.0f + exp(shift-current_activation/slope));
    sigmoid*=spatial_bias;//multiplies activation by space bias
    sigmoid*=feature_bias;//multiplies activation by feature bias
    return sigmoid;

}


void NeuronSigmoid::ComputeActivation(uint32_t global_time)


{
    //actual units of time (s)" (to be used in the probe class)
    m_current_Global_time=(float)m_t_step*global_time;

    float current_activation=0.0f;
    float *curr_activ;
    float spatial_bias=0.0f;
    float F_x=0.0f;
    for(uint32_t i=0;i<m_width; i++)
        for(uint32_t j=0; j<m_height; j++)
        {
            curr_activ=&(*m_sheet_activ)(i,j);
            current_activation=(*m_sheet_activ)(i,j);
            spatial_bias= (*m_spatial_bias)(i,j);

            F_x=EvaluateSigmoidFunctionWith(current_activation,
                                            m_shift, m_max_activation,
                                            m_slope,spatial_bias,
                                            m_feature_bias);
            *curr_activ=F_x;
        }
}
