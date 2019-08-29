/**
 * @brief   Connection class - stores the source and destination sheets
 *
 * @author  Asheer Bachoo, abachoo@gmail.com
 * @date    February 9, 2016
 */

#ifndef CONNECTION_H
#define CONNECTION_H

#include <map>
#include <tr1/memory>

#include <tarzann/Common.h>

namespace tarzann
{
    class GammaUnits;
    class GatingSignal;
    class ReceptiveField;
    class Sheet;

    class Connection
    {
        public:
            Connection(Sheet* source, Sheet* destination, std::string connection_name);

            Sheet* getSource();

            Sheet* getDestination();

            ReceptiveField* getReceptiveField();

            GatingSignal* getGatingSignal();

            GammaUnits* getGammaUnits();

            void addFilter(std::map<std::string,std::string>* params);

            SheetMapping getSrcDstMapping();

            SheetMapping getDstSrcMapping();

        private:
            std::tr1::shared_ptr<GatingSignal> m_gating_signal;
            std::tr1::shared_ptr<GammaUnits> m_gamma_units;
            std::tr1::shared_ptr<ReceptiveField> m_receptive_field;

            Sheet* m_source;
            Sheet* m_destination;

            SheetMapping m_src_dst_mapping;
            SheetMapping m_dst_src_mapping;

            void computeSheetMappings();

        protected:

    };
}
#endif // CONNECTION_H
