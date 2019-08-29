/**
 * @brief   Gating signal class - defines the signal (as a matrix) that goes
 *          from source to destination. Note that the matrix will be created
 *          in memory when this class is created and it will be the size of
 *          the destination sheet.
 * @author  Asheer Bachoo, abachoo@gmail.com
 * @date    February 9, 2016
 */

#ifndef GATINGSIGNAL_H
#define GATINGSIGNAL_H

#include <tr1/memory>

#include <tarzann/Common.h>

namespace tarzann
{
    class GammaUnits;
    class Matrix;
    class Sheet;

    class GatingSignal
    {
        public:
            GatingSignal(Sheet* source, Sheet* destination);

            Sheet* getSourceSheet();

            Sheet* getDestinationSheet();

            Matrix* getGatingSignalMatrix();

            void updateGatingSignal(GammaUnits* gamma_units,
                                    SheetMapping mapping,
                                    int x,
                                    int y);

        private:
            Sheet* m_source;
            Sheet* m_destination;
            std::tr1::shared_ptr<Matrix> m_gating_signal;
            int m_width;
            int m_height;
    };
}

#endif // GATINGSIGNAL_H
