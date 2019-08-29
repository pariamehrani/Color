#include <stdexcept>

#include <tarzann/PLattice.h>
#include <tarzann/RetinalLayer.h>

using namespace tarzann;
using namespace std;

PLattice::PLattice(InputType type, uint32_t width, uint32_t height)
{
    std::tr1::shared_ptr<Layer> retinal_layer =
            std::tr1::shared_ptr<Layer>( new RetinalLayer("INPUT_LAYER",
                                        type, width, height));

    m_layers_shared_ptrs.push_back(retinal_layer);
    m_layers["INPUT_LAYER"] = retinal_layer.get();
}

PLattice::~PLattice()
{
    m_layers.clear();
    m_layers_shared_ptrs.clear();
}

void PLattice::createLayer(std::string layer_name, tarzann::LayerType type)
{
    std::tr1::shared_ptr<Layer> layer =
            std::tr1::shared_ptr<Layer>( new Layer(layer_name, type));

    m_layers_shared_ptrs.push_back(layer);
    m_layers[layer_name] = layer.get();
}

void PLattice::createSheet(std::string layer_name, std::string sheet_name,
                           uint32_t width, uint32_t height,NeuronType nrn_type)
{
    Layer* layer = getLayer(layer_name);
    layer->createSheet(sheet_name, width, height,nrn_type);
}

Connection* PLattice::createConnection(std::string src_layer_name, std::string src_sheet_name,
                                       std::string dst_layer_name, std::string dst_sheet_name,
                                       std::string connection_name)
{
    Layer* src_layer = getLayer(src_layer_name);
    Sheet* src_sheet = src_layer->getSheet(src_sheet_name);

    Layer* dst_layer = getLayer(dst_layer_name);
    Sheet* dst_sheet = dst_layer->getSheet(dst_sheet_name);

    Connection* connection = nullptr;

    if(src_layer && src_sheet && dst_layer && dst_sheet)
        connection = dst_sheet->createConnection(src_sheet,connection_name);
    else
    {
        cout << "Cannot make connection: " << endl;
        cout << "(" << src_layer_name << "," << src_sheet_name << ") to ";
        cout << "(" << dst_layer_name << "," << dst_sheet_name << ")" <<endl;
    }
    return connection;
}

Layer* PLattice::getLayer(std::string layer_name)
{
    Layer* layer = nullptr;

    try
    {
        layer = m_layers.at(layer_name);
    }
    catch(const std::out_of_range& e)
    {
        return nullptr;
    }

    return layer;
}

void PLattice::getLayers(std::vector<Layer*>& layers)
{
    layers.clear();    

    for(uint32_t i=0; i<m_layers_shared_ptrs.size(); i++)
    {
        layers.push_back(m_layers_shared_ptrs[i].get());
    }
}

uint32_t PLattice::getNumLayers()
{
    return m_layers.size();
}

Sheet* PLattice::getSheet(std::string layer_name, std::string sheet_name)
{
    Layer* layer = getLayer(layer_name);

    if(layer != nullptr)
    {
        return layer->getSheet(sheet_name);
    }

    return nullptr;
}

void PLattice::getSheets(std::string layer_name,
                         std::vector<Sheet*>& sheets)
{
    Layer* layer = getLayer(layer_name);

    if(layer != nullptr)
    {
        return layer->getSheets(sheets);
    }
}

void PLattice::getConnections(Sheet* sheet,
                              std::vector<Connection*>& connections)
{
    sheet->getInputConnections(connections);
}

void PLattice::presentStimulus(Stimulus* stim)
{
    Layer* layer = getLayer("INPUT_LAYER");
    RetinalLayer* retinal_layer = reinterpret_cast<RetinalLayer*>(layer);
    retinal_layer->presentStimulus(stim);
}

void PLattice::removeStimulus()
{
    Layer* layer = getLayer("INPUT_LAYER");
    RetinalLayer* retinal_layer = reinterpret_cast<RetinalLayer*>(layer);
    retinal_layer->removeStimulus();
}


