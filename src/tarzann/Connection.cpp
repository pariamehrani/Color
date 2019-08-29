#include <tarzann/Connection.h>
#include <tarzann/GammaUnits.h>
#include <tarzann/GatingSignal.h>
#include <tarzann/ReceptiveField.h>
#include <tarzann/Sheet.h>

using namespace tarzann;

Connection::Connection(Sheet* source, Sheet* destination,
                       std::string connection_name)
{
    m_source = source;
    m_destination = destination;

    m_receptive_field = std::tr1::shared_ptr<ReceptiveField>
            ( new ReceptiveField(connection_name,5,5) );

    m_gating_signal =  std::tr1::shared_ptr<GatingSignal>
                ( new GatingSignal(destination, source) );

    computeSheetMappings();
}

Sheet* Connection::getSource()
{
    return m_source;
}

Sheet* Connection::getDestination()
{
    return m_destination;
}

ReceptiveField* Connection::getReceptiveField()
{
    return m_receptive_field.get();
}

void Connection::addFilter(std::map<std::string,std::string>* params)
{
    m_receptive_field->addFilter(params);
    Filter* filter = m_receptive_field->getFilter();

    m_gamma_units =
            std::tr1::shared_ptr<GammaUnits>
            ( new GammaUnits(m_destination->getWidth(),
                             m_destination->getHeight(),
                             filter->getXSize(),
                             filter->getYSize()));
}

GatingSignal* Connection::getGatingSignal()
{
    return m_gating_signal.get();
}

GammaUnits* Connection::getGammaUnits()
{
    return m_gamma_units.get();
}

void Connection::computeSheetMappings()
{
    float src_width = (float) m_source->getWidth();
    float src_height = (float) m_source->getHeight();

    float dst_width = (float) m_destination->getWidth();
    float dst_height = (float) m_destination->getHeight();

    m_src_dst_mapping.m_scale_x = dst_width / src_width;
    m_src_dst_mapping.m_scale_y = dst_height / src_height;

    m_dst_src_mapping.m_scale_x = src_width / dst_width;
    m_dst_src_mapping.m_scale_y = src_height / dst_height;
}

SheetMapping Connection::getSrcDstMapping()
{
    return m_src_dst_mapping;
}

SheetMapping Connection::getDstSrcMapping()
{
    return m_dst_src_mapping;
}

