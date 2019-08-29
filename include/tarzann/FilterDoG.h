#ifndef FILTER_DOG_H
#define FILTER_DOG_H

#include<tarzann/Matrix.h>
#include<tarzann/Filter.h>
#include<string>
#include<math.h>

namespace tarzann
{
    class FilterDoG: public Filter
    {
        public:

            FilterDoG(std::string f_name,
                      uint32_t width,
                      uint32_t height,
                      float sigma,
                      float aspect1,
                      float aspect2,
                      float ratio,
                      float orientation);

            ~FilterDoG();

            void createFilterDoG(float sigma,
                                 float aspect1,
                                 float aspect2,
                                 float ratio,
                                 float orientation);

            float max_f(float a, float b);

        protected:
    };
}
#endif
