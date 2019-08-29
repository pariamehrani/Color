#include<tarzann/FilterDoG.h>
#include<iostream>

using namespace tarzann;
using namespace std;

FilterDoG::FilterDoG(std::string f_name,
                     uint32_t width,
                     uint32_t height,
                     float sigma,
                     float aspect1,
                     float aspect2,
                     float ratio,
                     float orientation):

    Filter(f_name,DOG_Fltr,width,height)
{
    m_shift_x=0;
    m_shift_y=0;

    createFilterDoG(sigma,aspect1,aspect2,ratio,orientation);
}

void FilterDoG::createFilterDoG(float sigma,
                                float aspect1,
                                float aspect2,
                                float ratio,
                                float orientation)
{
    int x_coord, y_coord;
    int middleX = 0, middleY= 0;
    int filterSizeX = (int) m_width;
    int filterSizeY = (int) m_height;

    float l1_norm, l2_norm,
            gauss_density1,
            gauss_density2,
            DoG_density;

    float normaliz_fctr1, normaliz_fctr2,
            cos_funct, sin_funct, x1, y1;


    middleX = ( int )(filterSizeX/2 + m_shift_x);
    middleY = ( int )(filterSizeY/2 + m_shift_y);

    l1_norm = 0;
    l2_norm = 0;

    cos_funct = cos(M_PI*orientation/180.0);
    sin_funct = sin(M_PI*orientation/180.0);
    normaliz_fctr1 = 1/(sqrt(2*M_PI)*sigma);
    normaliz_fctr2 = 1/(sqrt(2*M_PI)*ratio*sigma);

    for (int y=-middleY;y<=middleY;y++){
        for (int x=-middleX;x<=middleX;x++){
            x1 = x*cos_funct - y*sin_funct;
            y1 = x*sin_funct + y*cos_funct;

            gauss_density1 = normaliz_fctr1 *
                    exp((-(x1*x1)-(aspect1*y1)*(aspect1*y1))
                     /(2*sigma*sigma));

            gauss_density2 = normaliz_fctr2 *
                    exp((-(x1*x1)-(aspect2*y1)*(aspect2*y1))
                    /(2*ratio*ratio*sigma*sigma));

            DoG_density = gauss_density1 - gauss_density2;

            x_coord = middleX + x;
            y_coord = middleY + y;

            if (y_coord >= filterSizeY)
            {
                y_coord = middleY + y - filterSizeY;
            }

            if (y_coord < 0)
            {
                y_coord = middleY + y + filterSizeY;
            }

            if (x_coord >= 0 && x_coord<filterSizeX)
            {
                (*this)(x_coord,y_coord) = DoG_density;
                l1_norm += DoG_density;
                l2_norm += DoG_density*DoG_density;
            }
        }
    }
    l1_norm/=(filterSizeX*filterSizeY);
    l2_norm = sqrt(l2_norm);

    for (int y=-middleY;y<=middleY;y++)
    {
        for (int x=-middleX;x<=middleX;x++)
        {
            x_coord = middleX + x;
            y_coord = middleY + y;

            if (x_coord >= 0 && x_coord <filterSizeX
                    && y_coord >= 0 && y_coord<filterSizeY)
            {
                (*this)(x_coord,y_coord)-= l1_norm;
                (*this)(x_coord,y_coord)/= l2_norm;
            }            
        }
    }
    //zero mean
    setZeroMean();
}

float FilterDoG::max_f(float a, float b)
{
    float rslt;
    rslt=a>b?a:b;
    return rslt;
}

FilterDoG::~FilterDoG()
{

}
