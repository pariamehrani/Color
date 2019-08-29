/**
 * @brief   Template class for 2D arrays.
 * @author  Asheer Bachoo, abachoo@gmail.com
 * @date    February 5, 2016
 */

#ifndef ARRAY2D_H
#define ARRAY2D_H

#include <stdlib.h>
#include <stdint.h>

namespace tarzann
{
    template <typename T> class Array2D
    {
        public:

            Array2D();

            Array2D(const uint32_t width, const uint32_t height);

            ~Array2D();

            const uint32_t getXSize();

            const uint32_t getYSize();

            const uint32_t getStep();

            const uint32_t getMemorySize();

            void* getData();


#ifdef __GNUC__
            __attribute__((always_inline))
#endif

            inline T& operator()(uint32_t x, uint32_t y)
            {
                    T* temp=m_rows[y];
                    return temp[x];
            }

#ifdef __GNUC__S
            __attribute__((always_inline))
#endif

            inline T operator()(uint32_t x, uint32_t y) const
            {
                    T* temp=m_rows[y];
                    return (temp)[x];
            }

        protected:

            void* m_data;

            T** m_rows;

            uint32_t m_width;
            uint32_t m_height;
            uint32_t m_row_bytes;
            uint32_t m_memory_size;

            void initMemory();
    };

    template <typename T> Array2D<T>::Array2D()
    {
        m_width = 0;
        m_height = 0;
        m_data = nullptr;
        m_rows = nullptr;
        m_row_bytes = 0;
        m_memory_size = 0;
    }

    template <typename T> Array2D<T>::
    Array2D(const uint32_t width, const uint32_t height)
    {
        m_width = width;
        m_height = height;
        m_data = nullptr;
        m_rows = nullptr;
        m_row_bytes = 0;
        m_memory_size = 0;

        initMemory();
    }

    template <typename T> Array2D<T>::~Array2D()
    {
        free(m_data);
        free(m_rows);
        //delete [] m_data;
        //delete [] m_rows;
    }

    template <typename T>
    const uint32_t Array2D<T>::getXSize()
    {
        return m_width;
    }

    template <typename T>
    const uint32_t Array2D<T>::getYSize()
    {
        return m_height;
    }

    template <typename T>
    const uint32_t Array2D<T>::getStep()
    {
        return m_row_bytes;
    }

    template <typename T>
    const uint32_t Array2D<T>::getMemorySize()
    {
        return m_memory_size;
    }

    template <typename T>
    void* Array2D<T>::getData()
    {
        return m_data;
    }

    template <typename T>
    void Array2D<T>::initMemory()
    {
        //number of bytes needed for a row of data
        m_row_bytes = m_width * sizeof(T);

        //TODO - Pad with zeros for
        //lengthen m_row_bytes to an integer multiple of 16 bytes
        //m_row_bytes = (m_row_bytes + 15) & ~15;

        //Make sure we are not an even power of 2 wide.
        //Will loop a few times for rowBytes <= 16.
        //while( 0 == (m_row_bytes & (m_row_bytes - 1) ) )
        //    m_row_bytes += 16;

        m_memory_size = m_row_bytes * m_height;

        //Set up the buffer
        m_data = calloc(1, m_memory_size+4);

        m_rows=(T**)calloc(1, m_height*sizeof(T*));

        for (uint32_t i= 0; i<m_height; i++)
        {
            m_rows[ i] = &(((T*)(m_data))[i*m_row_bytes/sizeof(T)]);
        }

//        m_data = new unsigned char[m_memory_size+4];

//        m_rows=(T**)new unsigned char[m_height*sizeof(T*)];

//        for (uint32_t i= 0; i<m_height; i++)
//        {
//            m_rows[i] = &(((T*)(m_data))[i*m_row_bytes/sizeof(T)]);
//        }
    }
}
#endif // ARRAY2D_H
