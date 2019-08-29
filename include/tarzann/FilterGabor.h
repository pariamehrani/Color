#ifndef FILTER_GABOR_H
#define FILTER_GABOR_H

#include <tarzann/Filter.h>
#include<string>

/** Gabor filter. */

namespace tarzann
{
    class FilterGabor : public Filter
    {
        public:
            FilterGabor(std::string f_name,
                        uint32_t width,
                        uint32_t height,
                        float sigma_x,
                        float sigma_y,
                        float psi,
                        float lambda,
                        float orientation);

            ~FilterGabor();

            void createGabor(float sigma_x,
                             float sigma_y,
                             float psi,
                             float lambda,
                             float orientation);
    };
}
#endif // FILTER_GABOR_H
