#include <stdexcept>
#include <string>
#include<iostream>

#include <tarzann/Common.h>
#include <tarzann/FeaturalReceptiveField.h>
#include <tarzann/Filter.h>
#include <tarzann/FilterDoG.h>
#include <tarzann/FilterType.h>
#include <tarzann/FilterGabor.h>
#include <tarzann/FilterGaussian.h>
#include <tarzann/FilterIdentity.h>
#include <tarzann/ReceptiveField.h>

using namespace std;
using namespace tarzann;

ReceptiveField::ReceptiveField(std::string rf_name,
                               const uint32_t width,
                               const uint32_t height)
{
    m_RF_name = rf_name;
    m_rf_width = width;
    m_rf_height = height;
}

std::string ReceptiveField::getRFname()
{
    return m_RF_name;
}

void ReceptiveField::addFilter(
                    std::map<std::string,std::string>* Params
                               )
{
    //read the filter type
    string set_Type=Params->find("fltr_Type")->second;

    //set the filter type
    FilterType fltr_type;

    if(set_Type=="gabor"    ){fltr_type=GABOR_Fltr;      }else
    if(set_Type=="gauss"    ){fltr_type=GAUSSIAN_Fltr;   }else
    if(set_Type=="dog"      ){fltr_type=DOG_Fltr;        }else
    if(set_Type=="identity" ){fltr_type=IDENTITY_Fltr;   }else
    if(set_Type=="file"     ){fltr_type=File_Fltr;       }


    //optional
    //saveFltrTypeAndParams(fltr_type,Params);

    std::string fltr_name;

    float       weight = getValue("weight",Params);
    uint32_t    height = getValue("height",Params);
    uint32_t    width = getValue("width",Params);
    uint32_t      shift_x= getValue("shiftX",Params);
    uint32_t      shift_y= getValue("shiftY",Params);

    m_featural_rf_buffer = new FeaturalReceptiveField(width, height);

    float       sigma;
    float       sigma_x;
    float       sigma_y;
    float       aspect1;
    float       aspect2;
    float       ratio;
    float       psi;
    float       lambda;

    //read and set filter orientation
    float fltr_orientat=getValue("orientation",Params);
    string orientat_str =Params->find("orientation")->second;

    switch(fltr_type)
    {
        case GABOR_Fltr:
            fltr_name=m_RF_name+"_GABOR_"+orientat_str;
            sigma_x = getValue("sigma_x",Params);
            sigma_y = getValue("sigma_y",Params);
            lambda = getValue("lambda",Params);
            psi = getValue("psi",Params);

            m_filter = new FilterGabor(fltr_name,
                                       width,
                                       height,
                                       sigma_x,
                                       sigma_y,
                                       psi,
                                       lambda,
                                       fltr_orientat);
            break;

        case GAUSSIAN_Fltr:
            fltr_name = m_RF_name+"_GAUSS_"+orientat_str;
            sigma_x = getValue("sigma_x",Params);
            sigma_y = getValue("sigma_y",Params);

            m_filter = new FilterGaussian(fltr_name,
                                          width,
                                          height,
                                          sigma_x,
                                          sigma_y,
                                          fltr_orientat);
            break;

        case DOG_Fltr:
            fltr_name = m_RF_name+"_DOG_"+orientat_str;
            aspect1 = getValue("aspect1",Params);
            aspect2 = getValue("aspect2",Params);
            sigma = getValue("sigma",Params);
            ratio = getValue("ratio",Params);

            m_filter= new FilterDoG(fltr_name,
                                    width,
                                    height,
                                    sigma,
                                    aspect1,
                                    aspect2,
                                    ratio,
                                    fltr_orientat);

            break;

        case File_Fltr:
            fltr_name=m_RF_name+"_FILE_"+orientat_str;
            break;

        case IDENTITY_Fltr:
            fltr_name=m_RF_name+"_IDENTITY";

            m_filter= new FilterIdentity(fltr_name,
                                         width,
                                         height);
            break;
    }

    m_filter->setShiftX(shift_x);
    m_filter->setShiftY(shift_y);
    m_filter->setWeight(weight);
    m_filters[m_filter->getFilterName()] = m_filter;
}

Filter* ReceptiveField::getFilter()
{
    return m_filter;
}


/*void ReceptiveField::saveFltrTypeAndParams(FilterType ftype,
                                   std::map<std::string, std::string>* Fparams)
{
        m_fltrParams_vctr.push_back(Fparams);
        m_fltrType_vctr.push_back(ftype);
}*/

//FilterType ReceptiveField::getFltType(int i)
//{
//    return m_fltrType_vctr[i];
//}

//std::map<std::string, std::string>* ReceptiveField::getFltrParams(int i)
//{
//    return m_fltrParams_vctr[i];
//}

float ReceptiveField::getValue(string s1,map<string,string>* Params)
{
   string s2=Params->find(s1)->second;
   float rslt = stof(s2,0);
   return rslt;

}

FeaturalReceptiveField* ReceptiveField::getFeaturalRFBuffer()
{
    return m_featural_rf_buffer;
}

ReceptiveField::~ReceptiveField()
{
    delete m_filter;
    delete m_featural_rf_buffer;
}
