#include <tarzann/FilterGaussian.h>
#include<iostream>

using namespace std;
using namespace tarzann;

FilterGaussian::FilterGaussian(std::string f_name,
                               uint32_t width,
                               uint32_t height,
                               float sigma_x,
                               float sigma_y,
                               float orientation):
    Filter (f_name, GAUSSIAN_Fltr, width, height)
{
    m_shift_x=0;
    m_shift_y=0;

    CreateGaussian (sigma_x,
                    sigma_y,
                    orientation);
}


void FilterGaussian::CreateGaussian (float sigma_x,
                                     float sigma_y,
                                     float orientation)
{
    int x_coord, y_coord;
    float fx, fy;
    float gauss_density = 0.0;
    float filter_sum = 0.0;
    int middleX = int(m_width/2);
    int middleY = int (m_height/2);

    float theta = M_PI*orientation/180.0;
    float cos_theta = cos(theta);
    float sin_theta = sin(theta);
    float sin_2theta = sin(2.0*theta);
    float sigma_x2 = sigma_x * sigma_x;
    float sigma_y2 = sigma_y * sigma_y;

    float a = cos_theta*cos_theta/(2.0*sigma_x2) + sin_theta*sin_theta/(2.0*sigma_y2);
    float b = -sin_2theta/(4.0*sigma_x2) + sin_2theta/(4.0*sigma_y2);
    float c = sin_theta*sin_theta/(2.0*sigma_x2) + cos_theta*cos_theta/(2.0*sigma_y2);

    for (int y=-middleY;y<=middleY;y++)
    {
        for (int x=-middleX;x<=middleX;x++)
        {
            fx = (float) x;
            fy = (float) y;

            gauss_density = exp(-((a*fx*fx) - (2.0*b*fx*fy) + (c*fy*fy)));

            x_coord = middleX + x;
            y_coord = middleY + y;

            filter_sum += gauss_density;

            (*this)(x_coord,y_coord)= gauss_density;
        }
    }

    for (int y=-middleY;y<=middleY;y++)
    {
        for (int x=-middleX;x<=middleX;x++)
        {
            x_coord = middleX + x;
            y_coord = middleY + y;
            (*this)(x_coord,y_coord) /= filter_sum;
        }
    }
}















