/**
 * @brief   Base class for running a network.
 * @author  Asheer Bachoo, abachoo@gmail.com
 * @date    February 10, 2016
 */

#ifndef COMPUTESTRATEGY_H
#define COMPUTESTRATEGY_H

#include <math.h>
#include <string>
#include <vector>

#include <tarzann/Common.h>
#include <tarzann/ControlSignalGenerator.h>

namespace tarzann
{
    class Connection;
    class Filter;
    class Matrix;
    class PLattice;
    class Sheet;

    struct FeaturalReceptiveField;
    struct InputToNeuron;

    class ComputeStrategy
    {
        public:
            ComputeStrategy(TaskType task_type,
                            int steps_per_attentive_cycle,
                            PLattice* plattice);

            ~ComputeStrategy();

            void run();

            void processSheet(Sheet* sheet);

            //competition
            void wtaCompetition(InputToNeuron* buffer, int n, float theta);
            void wtaComputeSumOfDeltas(InputToNeuron* buffer, int n, float theta);
            void wtaUpdateActivations(InputToNeuron* buffer, int n);
            void wtaUpdateGammas(InputToNeuron* buffer, int n);

            //process control signals

            //get/sum input weights
            void getInputWeights(Matrix* input,
                                 Matrix* output,
                                 Filter* filter,
                                 FeaturalReceptiveField* frf,
                                 int x,
                                 int y,
                                 SheetMapping mapping);

            float sumInputWeights(FeaturalReceptiveField* featural_rf);

            void loadConnectionsIntoBuffer(std::vector<Connection*> connections,
                                           InputToNeuron* buffer,
                                           int& n);

        protected:
            int m_clock_time;

            float m_theta_competition;

            PLattice* m_plattice;
            ControlSignalGenerator* m_control_signal_generator;
    };
}

#endif // COMPUTESTRATEGY_H
