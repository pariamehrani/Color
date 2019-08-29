/**
 * @brief   The base class of a sheet in the P-lattice of the visual hierarchy.
 * @author  Asheer Bachoo, abachoo@gmail.com
 * @date    February 1, 2016
 */

#ifndef SHEET_H
#define SHEET_H

#include <stdint.h>
#include <vector>
#include <string>
#include <tr1/memory>
#include <mutex>

#include <tarzann/Common.h>
#include <tarzann/NeuronType.h>
#include <tarzann/Neuron.h>
#include <tarzann/NeuronLinear.h>
#include <tarzann/NeuronLinear2.h>
#include <tarzann/NeuronSigmoid.h>
#include <tarzann/NeuronST.h>
#include <tarzann/NeuronST1.h>
#include <tarzann/SheetType.h>
#include <tarzann/Layer.h>

namespace tarzann
{
    class Connection;
    class GatingSignal;
    class Matrix;
    class Neuron;
    class NeuronLinear;
    class NeuronSigmoid;
    class NeuronST;
    class NeuronST1;
    class ReceptiveField;

    class Sheet
    {
        public:

            Sheet(std::string sheet_name,
                  uint32_t width,
                  uint32_t height,
                  NeuronType neuron_type,
                  LayerType layer_type);

            Sheet(std::string sheet_name,
                  uint32_t width,
                  uint32_t height,
                  NeuronType neuron_type,
                  SheetType sheet_type,
                  LayerType layer_type);

            virtual ~Sheet();

            virtual Connection* createConnection(Sheet* src_sheet, std::string connection_name);

            void computeNeuralResponse(uint32_t currnt_t);

            virtual Matrix* getOutput();

            Matrix* getBuffer();

            void updateOutput();

            void setSpatialBias(Matrix* spatial_bias);

            Matrix* getSpatialBias();

            void setFeatureBias(float feature_bias);

            float getFeatureBias();

            void getInputConnections(std::vector<Connection*>& connections);

            void getOutputConnections(std::vector<Connection*>& connections);

            Matrix* getGatingControl();

            void resetGatingUnits();

            GatingSignal *getInputGatingSignal(uint32_t index);

            void updateGatingControl();

            Matrix* getConvolvedInputs();

            Matrix* getIORMap();

            Matrix* getSuppressiveSurround();

            Array2D<H_curr>* getH_currs();

            Matrix* getCompetitionFlags();

            void findWinner();

            std::string getName();

            LayerType getLayerType();

            uint32_t getWidth();

            uint32_t getHeight();

            Neuron* getNeuron();

            SheetType getSheetType();

        private:
            void createTheNeuron(NeuronType nrn_type);

        protected:

            LayerType m_layer_type;

            SheetType m_sheet_type;

            std::mutex m_sheet_mutex;

            std::string m_name;

            float m_feature_bias;

            uint32_t m_width;
            uint32_t m_height;

            ObjectRegion m_winner_region;

            std::tr1::shared_ptr<Matrix> m_output;

            std::tr1::shared_ptr<Matrix> m_labels;

            std::tr1::shared_ptr<Array2D<H_curr>> m_h_currs;

            std::tr1::shared_ptr<Matrix> m_buffer;

            std::tr1::shared_ptr<Matrix> m_spatial_bias;

            std::tr1::shared_ptr<Matrix> m_competition_flags;

            std::tr1::shared_ptr<Matrix> m_gating_control;

            std::tr1::shared_ptr<Matrix> m_convolved_input;

            std::tr1::shared_ptr<Matrix> m_ior_map;

            std::tr1::shared_ptr<Matrix> m_suppressive_surround;

            //pointers to possible neurons
            std::tr1::shared_ptr<Neuron> m_neuron;

            std::vector< std::tr1::shared_ptr<Connection> > m_input_connections;
            std::vector< std::tr1::shared_ptr<Connection> > m_output_connections;

            std::vector< GatingSignal* > m_input_gating_signals;
            std::vector< GatingSignal* > m_output_gating_signals;

            //functions and methods
            void addInputGatingSignal(GatingSignal* g);

            void findLargestContiguousRegion(Matrix* binary,
                                             Matrix* strength,
                                             Matrix* labels);

            void createSuppressiveSurround();

            GatingSignal* getOutputGatingSignal(uint32_t index);

            void updateIORMap();
    };
}

#endif // SHEET_H
