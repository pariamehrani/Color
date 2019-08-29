#ifndef RECEPTIVE_FIELD_H
#define RECEPTIVE_FIELD_H

#include<map>
#include<string>
#include<vector>

#include <tarzann/FilterType.h>
#include <tarzann/FeaturalReceptiveField.h>
#include <tarzann/Filter.h>
#include <tarzann/FilterDoG.h>
#include <tarzann/FilterType.h>
#include <tarzann/FilterGabor.h>
#include <tarzann/FilterGaussian.h>
#include <tarzann/FilterIdentity.h>

#include <tarzann/Common.h>

namespace tarzann
{
    struct FeaturalReceptiveField;

    class ReceptiveField
    {

    public:
        ReceptiveField(std::string rf_name,
                       const uint32_t width,
                       const uint32_t height);

        ~ReceptiveField();

        std::string getRFname();

        void addFilter(std::map<std::string,std::string>* Params);

        void setupFilter(Filter* newFilter);

        Filter* getFilter();

        //void saveFltrTypeAndParams(FilterType ftype,
        //                    std::map<std::string, std::string>* Fparams);

        //FilterType getFltType(int i);

        //std::map<std::string, std::string>* getFltrParams(int i);


        float getValue(std::string s1,
                       std::map<std::string,std::string>* Params);

        FeaturalReceptiveField* getFeaturalRFBuffer();

    private:
        Filter* m_filter;
        FeaturalReceptiveField* m_featural_rf_buffer;
        std::map<std::string, Filter*> m_filters;
        std::string m_RF_name;


    protected:
        uint32_t  m_rf_width;
        uint32_t  m_rf_height;
        //std::vector<std::map<std::string,std::string>*> m_fltrParams_vctr;
        //std::vector<FilterType> m_fltrType_vctr;
    };
}

#endif // RECEPTIVE_FIELD_H

