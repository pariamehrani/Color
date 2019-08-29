/**
 * @brief   The layer class - used to store sheets.
 *          This should be viewed as an abstraction for sheets with a common
 *          function/purpose.
 * @author  Asheer Bachoo, abachoo@gmail.com
 * @date    February 9, 2016
 */

#ifndef LAYER_H
#define LAYER_H

#include <string>
#include <map>
#include <vector>
#include <stdint.h>
#include <tr1/memory>

#include <tarzann/NeuronType.h>
#include <tarzann/SheetType.h>

namespace tarzann
{
    class Sheet;

    enum LayerType
    {
        RETINAL_LAYER,
        INTERMEDIATE_LAYER,
        TOP_LAYER
    };

    class Layer
    {
        public:

            Layer(std::string name, LayerType type);

            virtual ~Layer();

            virtual void createSheet(std::string sheet_name,
                                     uint32_t width,
                                     uint32_t height,
                                     NeuronType nrn_type
                                     );

            virtual void createSheet(std::string sheet_name,
                                     uint32_t width,
                                     uint32_t height,
                                     NeuronType nrn_type,
                                     SheetType sheet_type
                                     );

            virtual Sheet* getSheet(std::string name);

            void getSheets (std::vector<Sheet*>& sheets);

            LayerType getType();

            std::string getName();

            uint32_t getNumberOfSheets();

        private:
            std::map<std::string, Sheet*> m_sheets;
            std::vector< std::tr1::shared_ptr<Sheet> > m_sheets_shared_ptrs;

            std::string m_name;

            LayerType m_layer_type;
    };
}

#endif // LAYER_H
