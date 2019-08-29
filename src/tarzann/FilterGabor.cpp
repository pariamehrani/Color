#include <tarzann/FilterGabor.h>
#include <math.h>
#include <iostream>

using namespace tarzann;
using namespace std;

FilterGabor::FilterGabor(std::string f_name,
                         uint32_t width,
                         uint32_t height,
                         float sigma_x,
                         float sigma_y,
                         float psi,
                         float lambda,
                         float orientation)
    :Filter (f_name, GABOR_Fltr, width, height)
{
    m_shift_x=0;
    m_shift_y=0;

    createGabor(sigma_x,
                sigma_y,
                psi,
                lambda,
                orientation);
}

FilterGabor::~FilterGabor()
{

}

void FilterGabor::createGabor(float sigma_x,
                              float sigma_y,
                              float psi,
                              float lambda,
                              float orientation)
{
    //sigmas squared
    float sigma_x2 = sigma_x * sigma_x;
    float sigma_y2 = sigma_y * sigma_y;

    // Create set of filters
    int filterSizeX = (int) m_width;
    int filterSizeY = (int) m_height;

    int middleX = filterSizeX / 2 + m_shift_x;
    int middleY = filterSizeY / 2 + m_shift_y;


    orientation = ((orientation + 90)/180.0)*M_PI; //angle of edge
    psi = (psi/180.0)*M_PI;

    float xPrime, yPrime;
    float a,c;
    float correction_factor = 0.0;

    for (int x=-middleX; x<=middleX; x++)
    {
        for (int y=-middleY; y<=middleY; y++)
        {
            xPrime =  (float)x * cos(orientation) + (float)y * sin(orientation);
            yPrime =  - (float)x * sin(orientation) + (float)y * cos(orientation);

            a = 1.0 / ( 2.0 * M_PI * sigma_x * sigma_y ) *
                    exp(-0.5 * (xPrime*xPrime / sigma_x2 +
                                yPrime*yPrime / sigma_y2) );

            c = cos( 2.0 * M_PI * xPrime / lambda + psi);

           int x_coord = middleX + x;
           int y_coord = middleY + y;

            (*this)(x_coord,y_coord) =a*c;

           correction_factor += a*c;
        }
    }

    correction_factor /= - (float) (filterSizeX*filterSizeY);

    for (int x=-middleX; x<=middleX; x++)
    {
        for (int y=-middleY; y<=middleY; y++)
        {
           int x_coord = middleX + x;
           int y_coord = middleY + y;

            (*this)(x_coord,y_coord) += correction_factor;
        }
    }
}
