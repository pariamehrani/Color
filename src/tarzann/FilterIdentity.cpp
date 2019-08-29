#include<tarzann/FilterIdentity.h>
#include <math.h>
#include <iostream>

using namespace tarzann;
using namespace std;

FilterIdentity::FilterIdentity(std::string f_name,
                               uint32_t width,
                               uint32_t height):
    Filter(f_name,IDENTITY_Fltr,width,height){

    CreateIdentityFilter();
}

void FilterIdentity::CreateIdentityFilter()
{
    setValue(0);
    for(int x=0;x<int(m_width);x++)
    {
      for(int y=0;y<int(m_height);y++)
      {
          if(x==int(m_width/2) && y==int(m_height/2))
          {
              (*this)(x,y)=1.0;
          }
      }
    }

}

FilterIdentity::~FilterIdentity()
{
}
