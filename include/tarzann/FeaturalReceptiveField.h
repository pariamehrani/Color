#ifndef FEATURAL_RECEPTIVE_FIELD_H
#define FEATURAL_RECEPTIVE_FIELD_H

#include <tarzann/GammaUnits.h>

namespace tarzann
{
    struct InputToNeuron
    {
        float m_g;
        float m_r;
        float m_r_prime;
        float m_sum_of_deltas;
        float m_gamma;

        int m_connection_id;
        int m_shift_x;
        int m_shift_y;

        void operator=(const InputToNeuron& rhs)
        {
            m_g = rhs.m_g;
            m_r = rhs.m_r;
            m_r_prime = rhs.m_r_prime;
            m_sum_of_deltas = rhs.m_sum_of_deltas;
            m_gamma = rhs.m_gamma;

            m_connection_id = rhs.m_connection_id;
            m_shift_x = rhs.m_shift_x;
            m_shift_y = rhs.m_shift_y;
        }
    };

    struct FeaturalReceptiveField
    {
        float** m_g;
        float** m_r;
        float** m_gammas;
        int m_width;
        int m_height;
        int m_center_x;
        int m_center_y;

        FeaturalReceptiveField(int width, int height)
        {
            m_width = width;
            m_height = height;
            m_center_x = 0;
            m_center_y = 0;

            m_g = new float*[m_height];
            m_r = new float*[m_height];
            m_gammas = new float*[m_height];

            for (int i=0; i<m_height; i++)
            {
                m_g[i] = new float[m_width];
                m_r[i] = new float[m_width];
                m_gammas[i] = new float[m_width];
            }
        }

        void setGammas(float val)
        {
            for (int i=0; i<m_height; i++)
            {
                for (int j=0; j<m_width; j++)
                {
                    m_gammas[i][j] = val;
                }
            }
        }

        void loadGammaUnits(GammaUnits* gamma_units,
                            int x,
                            int y,
                            float weight=1.0)
        {
            bool flag;

            gamma_units->seekUnit(x,y);

            for (int i = 0; i < m_height; i++)
            {
                for (int j = 0; j < m_width; j++)
                {
                    gamma_units->readBit(flag);
                    if(flag)
                        m_gammas[i][j] = weight;
                    else
                        m_gammas[i][j] = 0.0;
                }
            }
        }

        ~FeaturalReceptiveField()
        {
            for (int i=0; i<m_height; i++)
            {
                delete [] m_g[i];
                delete [] m_r[i];
                delete [] m_gammas[i];
            }

            delete [] m_g;
            delete [] m_r;
            delete [] m_gammas;
        }
    };
}

#endif // FEATURAL_RECEPTIVE_FIELD_H

