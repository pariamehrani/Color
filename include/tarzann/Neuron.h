#ifndef _NEURON_H_
#define _NEURON_H_
/*#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
#include <math.h>
#include <algorithm>*/

#include <stdint.h>

namespace tarzann
{
    class Sheet;

    class Neuron
    {

        public:
            Neuron(Sheet* sheet);
            ~Neuron();

            virtual void SolveEqUsingRK4andUpdate(float *current_activation,
                                                 float current_t,
                                                 float t_step,
                                                 float t_step_sixths,
                                                 float K_array[4]);


            virtual void ComputeActivation(uint32_t global_time);

        protected:
            Sheet* m_sheet;
    };

}
#endif
