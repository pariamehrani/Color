#include <tarzann/GammaUnits.h>
#include <tarzann/GatingSignal.h>
#include <tarzann/Matrix.h>
#include <tarzann/Sheet.h>

using namespace tarzann;

GatingSignal::GatingSignal(Sheet* source, Sheet* destination)
{
    m_source = source;
    m_destination = destination;

    m_width = (int) destination->getWidth();
    m_height = (int) destination->getHeight();

    //NEED TO THINK AGAIN, BECAUSE WHEN SEND BACK TO SOURCE AND SUM GATINGSIGNAL MATRICESS
    //ALL HAVE DIFFERENT SIZES!!
    m_gating_signal = std::tr1::shared_ptr<Matrix>(new Matrix(m_width, m_height));
    m_gating_signal->setValue(0.0);
}

void GatingSignal::updateGatingSignal(GammaUnits* gamma_units,
                                      SheetMapping mapping,
                                      int x,
                                      int y)
{
    gamma_units->seekUnit(x,y);
    bool flag;

    int width = gamma_units->getRFWidth();
    int height = gamma_units->getRFHeight();
    int hw = width/2;
    int hh = height/2;
    int dx, dy;
    int gating_signal;
    int count_x = (int) mapping.m_scale_x;
    int count_y = (int) mapping.m_scale_y;

    for (int iy = -hh; iy<= hh; iy++)
    {
        for (int ix = -hw; ix <= hw; ix++)
        {
            gamma_units->readBit(flag);

            for(int cy=0; cy<count_y; cy++)
            {
                for(int cx=0; cx<count_x; cx++)
                {
                    dx = ((float) (x + ix)) * mapping.m_scale_x + cx;
                    dy = ((float) (y + iy)) * mapping.m_scale_y + cy;

                    if(dx >= 0 && dy >= 0 && dx < m_width && dy < m_height)
                    {
                        gating_signal = (*m_gating_signal)(dx,dy);
                        if(flag)
                        {
                            (*m_gating_signal)(dx,dy) = 1.0;
                        }
                        else if (gating_signal < 1.0)
                        {
                            (*m_gating_signal)(dx,dy) = -1.0;
                        }
                    }
                }
            }
        }
    }
}

Sheet* GatingSignal::getSourceSheet()
{
    return m_source;
}

Sheet* GatingSignal::getDestinationSheet()
{
    return m_destination;
}

Matrix* GatingSignal::getGatingSignalMatrix()
{
    return m_gating_signal.get();
}

