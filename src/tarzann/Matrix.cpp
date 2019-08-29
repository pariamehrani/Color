#include <tarzann/Matrix.h>

using namespace tarzann;
using namespace std;

Matrix::Matrix(const uint32_t width, const uint32_t height):Array2D<float>(width, height)
{
    tarzannAssert(width>0 &&
                  height>0,
                  "Cannot create matrix with width or height equal to zero.");

    m_width = width;
    m_height  = height;
    m_created = true ;
}

void Matrix::copy(const Matrix& rhs)
{
    tarzannAssert(m_width==rhs.m_width &&
                  m_height==rhs.m_height,
                  "Matrices are not the same size.");

    for (unsigned int j=0; j<rhs.m_height; j++)
        for (unsigned int i=0; i<rhs.m_width; i++)
            (*this)(i,j) = rhs(i,j);
}

void Matrix::setPixelTo(uint32_t i,uint32_t j,float value)
{
    (*this)(i,j)=value;
}

void Matrix::operator=( const Matrix& rhs)
{
    tarzannAssert(m_width==rhs.m_width &&
                  m_height==rhs.m_height,
                  "Matrices are not the same size.");

    for (unsigned int j=0; j<m_height; j++)
        for (unsigned int i=0; i<m_width; i++)
            (*this)(i,j) = rhs(i,j);
}

void Matrix::setZeroMean()
{
    addScalar(-1.0*average());
}

void Matrix::addScalar(float value)
{
    uint32_t i,j;

    for (j= 0; j<m_height; j++)
        for (i= 0; i<m_width; i++)
            (*this)(i,j)= (*this)(i,j)+value;
}

float Matrix::average()
{
    return sumAll()/(m_height*m_width);
}

Winner Matrix::getMaxActivation()
{
    Winner max_activation;
    uint32_t i_max=0,j_max=0;
    float max_resp=0;
    float resp=0;

    for(uint32_t i=0; i<m_height; i++)
    {
        for(uint32_t j=0; j<m_width; j++)
        {
            resp=(*this)(j,i);
            if(resp>max_resp)
            {
                max_resp=resp;
                i_max=i;
                j_max=j;
            }
        }
    }

    max_activation.x=j_max;
    max_activation.y=i_max;
    max_activation.z=max_resp;

    return max_activation;
}

Winner Matrix::getMaxActivation(Matrix* ior_map)
{
    tarzannAssert(m_width==ior_map->getXSize() &&
                  m_height==ior_map->getYSize(),
                  "Matrices are not the same size.");

    Winner max_activation;
    uint32_t i_max=0,j_max=0;
    float max_resp=0;
    float resp=0;
    float ior;

    for(uint32_t i=0; i<m_height; i++)
    {
        for(uint32_t j=0; j<m_width; j++)
        {
            resp=(*this)(j,i);
            ior = (*ior_map)(j,i);

            if(resp>max_resp && ior==0.0)
            {
                max_resp=resp;
                i_max=i;
                j_max=j;
            }
        }
    }

    max_activation.x=j_max;
    max_activation.y=i_max;
    max_activation.z=max_resp;

    return max_activation;
}

void Matrix::scaleValues(float minScaleValue, float maxScaleValue)
{
    float localMin, localMax;
    assert( minScaleValue < maxScaleValue);

    localMin = getMinValue();
    localMax = getMaxValue();

    if (localMin == localMax)
        localMax+=0.00001;

    assert(localMin < localMax);

    for (uint32_t j=0; j<m_height; j++)
        for (uint32_t i=0; i<m_width; i++)
            (*this)(i,j) = (maxScaleValue-minScaleValue) *
                ( (*this)(i,j)-localMin) / (localMax - localMin) + minScaleValue;
}

float Matrix::getMinValue()
{
    float minValue = (*this)(0,0);
    uint32_t i,j;

    for (j= 0; j<m_height; j++)
        for (i= 0; i<m_width; i++)
            if ((*this)(i,j)<minValue)
                minValue = (*this)(i,j);

    return minValue;
}

float Matrix::getMaxValue()
{
    float maxValue = (*this)(0,0);
    uint32_t i,j;

    for (j= 0; j<m_height; j++)
        for (i= 0; i<m_width; i++)
            if ((*this)(i,j)>maxValue)
                maxValue = (*this)(i,j);

    return maxValue;
}

Matrix::~Matrix()
{

}
