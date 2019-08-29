/** Gaussian filter. */

#ifndef FILTER_GAUSSIAN
#define FILTER_GAUSSIAN
#include<tarzann/Matrix.h>
#include<math.h>
#include<tarzann/Filter.h>

namespace tarzann {

class Matrix;


class FilterGaussian: public Filter{

public:

    FilterGaussian(std::string f_name,
                   uint32_t width,
                   uint32_t height,
                   float sigma_x,
                   float sigma_y,
                   float orientation);

    void CreateGaussian(float sigma_x,
                        float sigma_y,
                        float orientation);

protected:

    /** Constructor.
    Formula: f(i,j)=1/[sqrt(2PI)*sigm] *
    exp{-[x^2 + (aspect * y)^2]/(2sigma^2)}
    where
    x=i*cos(orientation)-j*sin(orientation)
    y=i*sin(orientation)+j*cos(orientation)
    */

    /** Constructor.
    Formula: f(i,j)=1/[sqrt(2PI)*sigma*ratio] *
    exp{-[x^2 + (aspect * y)^2]/(2(sigma*ratio)^2)}
    where
    x=i*cos(orientation)-j*sin(orientation)
    y=i*sin(orientation)+j*cos(orientation)
    */

};

}
#endif
