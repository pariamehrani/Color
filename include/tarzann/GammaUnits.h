/**
 * @author  Asheer Bachoo, abachoo@gmail.com
 * @date    May 12, 2016
 */

#ifndef GAMMAUNITS_H
#define GAMMAUNITS_H

#include <stdint.h>

namespace tarzann
{
    class GammaUnits
    {
        public:
            GammaUnits(const uint32_t width, const uint32_t height,
                       const uint32_t rf_width, const uint32_t rf_height);

            ~GammaUnits();

            //random access
            bool getGammaBit(int x, int y, int dx, int dy);

            void setGammaBit(int x, int y, int dx, int dy, bool bit);

            //sequential access
            void seekUnit(int x, int y);
            int writeBit(bool bit);
            int readBit(bool& bit);
            int flushBits();

            //pointer to data for neuron (x,y)
            unsigned char* getUnitDataPtr(int x, int y);

            //reset units to zero
            void resetGammaUnits();

            uint32_t getRFWidth();

            uint32_t getRFHeight();

        private:
            int m_flag;
            int m_current_byte_position;
            int m_current_bit_position;
            unsigned char m_current_byte;

            uint32_t m_width;
            uint32_t m_height;
            uint32_t m_rf_width;
            uint32_t m_rf_height;

            int m_half_rf_width;
            int m_half_rf_height;

            uint32_t m_bytes_per_rf;

            unsigned char* m_data;
            uint32_t m_data_length;
    };
}

#endif // GATINGSIGNAL_H
