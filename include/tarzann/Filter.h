#ifndef _FILTER_H_
#define _FILTER_H_

#include<string>
#include<vector>
#include<map>

#include<tarzann/Matrix.h>
#include<tarzann/FilterType.h>

namespace tarzann {

class Filter : public Matrix
{
    public:
        Filter(std::string fltr_name,
               FilterType fltr_type,
               const uint32_t width,
               const uint32_t height);

        FilterType getFilterType();

        std::string getFilterName();

        uint32_t getFilterWidth();

        uint32_t getFilterHeight();

        void setWeight(float w);

        void setShiftX (int x);

        void setShiftY (int y);

        int getShiftX();

        int getShiftY();

    protected:
        int m_shift_x;
        int m_shift_y;
        float m_weight;

        std::string m_filter_name;
        FilterType  m_filter_type;
};

}

#endif // FILTER_H
