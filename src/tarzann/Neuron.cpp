#include <tarzann/Neuron.h>
#include <tarzann/Sheet.h>

using namespace tarzann;

Neuron::Neuron(Sheet* sheet)
{
    m_sheet = sheet;
}

Neuron::~Neuron()
{

}

void Neuron::SolveEqUsingRK4andUpdate(float *current_activation,
                                     float current_t,
                                     float t_step,
                                     float t_step_sixths,
                                     float K[4])
{
	
    //Define initial conditions
    float initial_activation=*current_activation;
    float updated_activation=0.0;

    //getting algorithm constants
//    float k1=K_array[0];
//    float k2=K_array[1];
//    float k3=K_array[2];
//    float k4=K_array[3];

    //computing activation at current_time+t_step
    updated_activation=initial_activation+t_step_sixths*(K[0]+2.0*K[1]+2.0*K[2]+K[3]);

    //passing back the result to the original direction in memory
    *current_activation = updated_activation;
}

			
    void Neuron::ComputeActivation(uint32_t global_time){ }
		
		


