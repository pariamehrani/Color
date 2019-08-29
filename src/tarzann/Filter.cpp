#include<tarzann/Filter.h>

using namespace tarzann;

Filter::Filter(std::string fltr_name,
               FilterType fltr_type,
               const uint32_t width,
               const uint32_t height)
    :Matrix(width,height)
{
    m_filter_name = fltr_name;
    m_filter_type = fltr_type;
    m_shift_x = 0;
    m_shift_y = 0;
    m_weight = 1.0;
}

FilterType Filter::getFilterType()
{
    return m_filter_type;
}

std::string Filter::getFilterName()
{
    return m_filter_name;
}

void Filter::setShiftX(int x)
{
    m_shift_x = x;
}

void Filter::setShiftY(int y)
{
    m_shift_y = y;
}

void Filter::setWeight(float w)
{
    m_weight = w;

    for (uint32_t j=0; j<m_height; j++)
    {
        for (uint32_t i=0; i<m_width; i++)
        {
            (*this)(i,j)*=m_weight;
        }
    }
}

int Filter::getShiftX()
{
    return m_shift_x;
}

int Filter::getShiftY()
{
    return m_shift_y;
}

uint32_t Filter::getFilterWidth()
{
    return m_width;
}

uint32_t Filter::getFilterHeight()
{
    return m_height;
}

