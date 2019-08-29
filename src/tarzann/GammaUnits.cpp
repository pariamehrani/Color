#include <tarzann/Debug.h>
#include <tarzann/GammaUnits.h>

using namespace tarzann;
using namespace std;

GammaUnits::GammaUnits(const uint32_t width, const uint32_t height,
                       const uint32_t rf_width, const uint32_t rf_height)
{
    m_width = width;
    m_height = height;
    m_rf_width = rf_width;
    m_rf_height = rf_height;

    m_current_byte_position = -1;
    m_current_bit_position = -1;

    m_half_rf_width = rf_width >> 1;
    m_half_rf_height = rf_height >> 1;

    if ( (m_rf_width*m_rf_height / 8) ==0 )
        m_bytes_per_rf = m_rf_width*m_rf_height / 8;
    else
        m_bytes_per_rf = (m_rf_width*m_rf_height / 8) + 1;

    //cout << "RF = (" << m_rf_width << "," << m_rf_height << ")" <<endl;
    //cout << "HALF RF = (" << m_half_rf_width << "," << m_half_rf_height << ")" <<endl;
    //cout << "Bytes per RF = " << m_bytes_per_rf << endl;

    m_data_length = m_width*m_height*m_bytes_per_rf;
    m_data = new unsigned char[m_data_length];
}

void GammaUnits::resetGammaUnits()
{
    for (int i=0; i<m_data_length; i++)
    {
        *(m_data + i) = 255;
    }
}

bool GammaUnits::getGammaBit(int x, int y, int dx, int dy)
{
    unsigned char* data_ptr = m_data + ( y * m_width + x ) * m_bytes_per_rf;

    uint32_t bit_idx = ( dy + m_half_rf_height) * m_rf_width + (dx + m_half_rf_width);
    //uint32_t bit_idx = dy * m_rf_width + dx;
    uint32_t byte_offset = bit_idx / 8;
    uint32_t bit_offset = bit_idx % 8;

    return data_ptr[byte_offset] & (1 << bit_offset);
}

void GammaUnits::setGammaBit(int x, int y, int dx, int dy, bool bit)
{
    unsigned char* data_ptr = m_data + ( y * m_width + x ) * m_bytes_per_rf;

    uint32_t bit_idx = ( dy + m_half_rf_height) * m_rf_width + (dx + m_half_rf_width);
    //uint32_t bit_idx = dy * m_rf_width + dx;
    uint32_t byte_offset = bit_idx / 8;
    uint32_t bit_offset = bit_idx % 8;

    if(bit)
        data_ptr[byte_offset] |= (1 << bit_offset);
    else
        data_ptr[byte_offset] &= ~(1 << bit_offset);
    //data_ptr[byte_offset] |= (1 << bit_offset);
}

unsigned char* GammaUnits::getUnitDataPtr(int x, int y)
{
    return (m_data + ( y * m_width + x ) * m_bytes_per_rf);
}

void GammaUnits::seekUnit(int x, int y)
{
    m_current_byte_position = ( y * m_width + x ) * m_bytes_per_rf;
    m_current_byte = *(m_data + m_current_byte_position);
    m_current_bit_position = 7;
}

int GammaUnits::writeBit(bool bit)
{
    if(bit)
        m_current_byte |= (1 << m_current_bit_position);
    else
        m_current_byte &= ~(1 << m_current_bit_position);

    m_current_bit_position--;

    if(m_current_bit_position==-1)
    {
        flushBits();

        m_current_byte_position++;
        m_current_byte = *(m_data + m_current_byte_position);
        m_current_bit_position = 7;
    }
}

int GammaUnits::readBit(bool& bit)
{
    bit = m_current_byte & (1 << m_current_bit_position);

    m_current_bit_position--;

    if(m_current_bit_position==-1)
    {
        m_current_byte_position++;
        m_current_byte = *(m_data + m_current_byte_position);
        m_current_bit_position = 7;
    }
}

int GammaUnits::flushBits()
{
    *(m_data + m_current_byte_position) = m_current_byte;
}

uint32_t GammaUnits::getRFWidth()
{
    return m_rf_width;
}

uint32_t GammaUnits::getRFHeight()
{
    return m_rf_height;
}

GammaUnits::~GammaUnits()
{
    delete [] m_data;
}

