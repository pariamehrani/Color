#ifndef FILTER_IDENTITY_H
#define FILTER_IDENTITY_H

#include <tarzann/Filter.h>
#include<string>

/** Identity filter. */
namespace tarzann {

    class FilterIdentity : public Filter{

    public:

        FilterIdentity(std::string f_name,
                       uint32_t width,
                       uint32_t height);

        void CreateIdentityFilter();


        ~FilterIdentity();

    };

}



#endif
