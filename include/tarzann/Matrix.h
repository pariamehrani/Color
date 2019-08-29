/**
 * @brief   Matrix class - this is a 2D array of floats.
 * @author  Asheer Bachoo, abachoo@gmail.com
 * @date    February 9, 2016
 */

#ifndef MATRIX_H
#define MATRIX_H

#include <string.h>
#include <stdio.h>
#include <iostream>
#include <assert.h>

#include <tarzann/Common.h>
#include <tarzann/Debug.h>
#include <tarzann/Array2D.h>

namespace tarzann
{
    class Matrix : public Array2D<float>
    {
        public:
            Matrix(const uint32_t width, const uint32_t height);

            void operator=( const Matrix& rhs);

            void setPixelTo(uint32_t i,uint32_t j,float value);

            void copy(const Matrix& rhs);

            void setZeroMean();

            void addScalar(float value);

            float average();

            void scaleValues(float minScaleValue, float maxScaleValue);

            float getMinValue();

            float getMaxValue();

            Matrix(Matrix &matrix);

            inline void setValue(float value)
            {
                uint32_t i,j;
                for (j= 0; j<m_height; j++)
                    for (i= 0; i<m_width; i++)
                        (*this)(i,j)=value;
            }

            inline float sumAll()
            {
                float sum = 0;
                uint32_t i,j;

                for (j= 0; j<m_height; j++)
                    for (i= 0; i<m_width; i++)
                        sum += (*this)(i,j);
                return sum;
            }

            Winner getMaxActivation();

            Winner getMaxActivation(Matrix* ior_map);

            ~Matrix();

        protected:
            bool m_created;
    };
}

#endif // MATRIX_H
