/**
 * @brief   PLattice class that store layers, sheets and their connections.
 * @author  Asheer Bachoo, abachoo@gmail.com
 * @date    February 9, 2016
 */

#ifndef PLATTICE_H
#define PLATTICE_H

#include<iostream>
#include <string>
#include <map>
#include <vector>
#include <tr1/memory>
#include<tarzann/Stimulus.h>

#include <tarzann/Connection.h>
#include <tarzann/NeuronType.h>
#include <tarzann/RetinalLayer.h>
#include <tarzann/Sheet.h>

namespace tarzann
{
    class Matrix;
    class Sheet;
    class Stimulus;

    class PLattice
    {
        public:

            PLattice(InputType type, uint32_t width, uint32_t height);

            virtual ~PLattice();

            //Functions to create objects in the lattice
            virtual void createLayer(std::string layer_name,
                                     tarzann::LayerType type);

            virtual void createSheet(std::string layer_name,
                                     std::string sheet_name,
                                     uint32_t width,
                                     uint32_t height,
                                     NeuronType nrn_type);

            virtual Connection* createConnection(std::string src_layer_name,
                                                 std::string src_sheet_name,
                                                 std::string dst_layer_name,
                                                 std::string dst_sheet_name,
                                                 std::string connection_name);

            //functions for layers
            Layer* getLayer(std::string layer_name);

            void getLayers(std::vector<Layer*>& layers);

            uint32_t getNumLayers();

            //functions for sheets
            Sheet* getSheet(std::string layer_name,
                            std::string sheet_name);

            void getSheets(std::string layer_name,
                           std::vector<Sheet*>& sheets);

            //get connections to a sheet
            void getConnections(Sheet* sheet,
                                std::vector<Connection*>& connections);

            //stimulus functions
            void presentStimulus(Stimulus* stim);

            void removeStimulus();

        protected:
            std::vector< std::tr1::shared_ptr<Layer> > m_layers_shared_ptrs;
            std::map< std::string, Layer* > m_layers;
    };
}

#endif // PLATTICE_H
