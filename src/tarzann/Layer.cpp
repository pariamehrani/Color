#include <stdexcept>
#include <tarzann/Debug.h>
#include <tarzann/Layer.h>
#include <tarzann/Sheet.h>

using namespace tarzann;

Layer::Layer(std::string layer_name, LayerType type)
{
    m_name = layer_name;
    m_layer_type = type;
}

void Layer::createSheet(std::string sheet_name,
                        uint32_t width,
                        uint32_t height,
                        NeuronType nrn_type)
{
    std::tr1::shared_ptr<Sheet> sheet =
            std::tr1::shared_ptr<Sheet>
            (new Sheet(sheet_name, width, height, nrn_type, m_layer_type));

    m_sheets_shared_ptrs.push_back(sheet);

    m_sheets[sheet->getName()] = sheet.get();
}

void Layer::createSheet(std::string sheet_name,
                        uint32_t width,
                        uint32_t height,
                        NeuronType nrn_type,
                        SheetType sheet_type)
{
    std::tr1::shared_ptr<Sheet> sheet =
            std::tr1::shared_ptr<Sheet>
            (new Sheet(sheet_name, width, height, nrn_type, sheet_type, m_layer_type));

    m_sheets_shared_ptrs.push_back(sheet);

    m_sheets[sheet->getName()] = sheet.get();
}

Sheet* Layer::getSheet(std::string name)
{
    Sheet* sheet = nullptr;

    try
    {
        sheet = m_sheets.at(name);
    }
    catch(const std::out_of_range& e)
    {
        return nullptr;
    }

    return sheet;
}

void Layer::getSheets (std::vector<Sheet*>& sheets)
{
    sheets.clear();

    for (uint32_t i=0; i<m_sheets_shared_ptrs.size(); i++)
    {
        sheets.push_back(m_sheets_shared_ptrs[i].get());
    }
}

LayerType Layer::getType()
{
    return m_layer_type;
}

std::string Layer::getName()
{
    return m_name;
}

uint32_t Layer::getNumberOfSheets()
{
    return m_sheets.size();
}

Layer::~Layer()
{
    m_sheets_shared_ptrs.clear();
    m_sheets.clear();
}
