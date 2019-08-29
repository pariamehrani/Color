/**
 * @brief   Retinal layer class for presenting a stimulus to the network.
 * @author  Asheer Bachoo, abachoo@gmail.com
 * @date    February 17, 2016
 */

#ifndef RETINAL_LAYER_H
#define RETINAL_LAYER_H

#include <tr1/memory>
#include <tarzann/Layer.h>

namespace tarzann
{
    class Matrix;
    class Sheet;
    class Stimulus;

    enum InputType
    {
        COLOUR_INPUT,
        GREYSCALE_INPUT
    };

    class RetinalLayer : public Layer
    {
        public:

            RetinalLayer(std::string name, InputType input_type, uint32_t width, uint32_t height);

            ~RetinalLayer();

            void presentStimulus(Stimulus* stimulus);

            void removeStimulus();

        private:

            void setupColourInput(uint32_t width, uint32_t height);

            void setupGreyscaleInput(uint32_t width, uint32_t height);

            //std::vector< std::tr1::shared_ptr<Sheet> > m_sheet_objects;

            InputType m_input_type;

            uint32_t m_width;
            uint32_t m_height;
    };
}

#endif // RETINAL_LAYER_H
