#include <stdexcept>
#include <tarzann/RetinalLayer.h>
#include <tarzann/Sheet.h>
#include <tarzann/Stimulus.h>

using namespace tarzann;

RetinalLayer::RetinalLayer(std::string name, InputType input_type, uint32_t width, uint32_t height):
    Layer(name, RETINAL_LAYER)
{
    m_width = width;
    m_height = height;

    m_input_type = input_type;

    if (m_input_type == COLOUR_INPUT)
        setupColourInput(width, height);
    else if(m_input_type == GREYSCALE_INPUT)
        setupGreyscaleInput(width, height);
}

void RetinalLayer::setupColourInput(uint32_t width, uint32_t height)
{
    createSheet("RED",width,height,no_nrn);
    createSheet("GREEN",width,height,no_nrn);
    createSheet("BLUE",width,height,no_nrn);
    createSheet("LUMINANCE",width,height,no_nrn);
}

void RetinalLayer::setupGreyscaleInput(uint32_t width, uint32_t height)
{
    createSheet("GREY",width,height,no_nrn);
}

void RetinalLayer::presentStimulus(Stimulus* stimulus)
{
    uint32_t width = stimulus->getWidth();
    uint32_t height = stimulus->getHeight();

    assert(height==m_height && width==m_width);

    *getSheet("RED")->getOutput() = *stimulus->getMatrix(0);
    *getSheet("GREEN")->getOutput() = *stimulus->getMatrix(1);
    *getSheet("BLUE")->getOutput() = *stimulus->getMatrix(2);
    *getSheet("LUMINANCE")->getOutput() = *stimulus->getMatrix(3);
}

void RetinalLayer::removeStimulus()
{
    getSheet("RED")->getOutput()->setValue(0.0);
    getSheet("GREEN")->getOutput()->setValue(0.0);
    getSheet("BLUE")->getOutput()->setValue(0.0);
    getSheet("LUMINANCE")->getOutput()->setValue(0.0);
}

RetinalLayer::~RetinalLayer()
{

}
