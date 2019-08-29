#ifndef COMMON_FUNCTIONS_H
#define COMMON_FUNCTIONS_H

#include <iostream>
#include <math.h>

#define IOR_CYCLES 4.0

using namespace std;

namespace tarzann
{
    struct Point2D
    {
        float x;
        float y;

        Point2D()
        {
            x = 0.0;
            y = 0.0;
        }

        Point2D(float x, float y)
        {
            this->x = x;
            this->y = y;
        }

        Point2D& operator+(const Point2D& rhs)
        {
            x += rhs.x;
            y += rhs.y;
            return *this;
        }

        Point2D& operator/=(const float rhs)
        {
            x /= rhs;
            y /= rhs;
            return *this;
        }

        void operator=(const Point2D& rhs)
        {
            x = rhs.x;
            y = rhs.y;
        }
    };

    struct SheetMapping
    {
        float m_scale_x;
        float m_scale_y;
    };

    struct Winner
    {
        int x;
        int y;
        float z;
    };

    struct H_curr
    {
        float h_slow;
        float h_fast;
    };

    struct ObjectRegion
    {
        float strength;
        float max_response;
        float size;
        float rleft;
        float rright;
        float rtop;
        float rbottom;
        float radius;
        float width;
        float height;

        Point2D center;

        ObjectRegion()
        {
            reset();
        }

        void reset()
        {
            strength = 0.0;
            max_response = 0.0;
            center.x = 0.0;
            center.y = 0.0;
            size = 0.0;
            rleft = 10000;
            rright = -10000;
            rtop = 10000;
            rbottom = -10000;
            radius = 0;
            width = -1;
            height = -1;
        }

        void operator=(const ObjectRegion& rhs)
        {
            strength = rhs.strength;
            max_response = rhs.max_response;
            center = rhs.center;
            size = rhs.size;
            rleft = rhs.rleft;
            rright = rhs.rright;
            rtop = rhs.rtop;
            rbottom = rhs.rbottom;
            radius = rhs.radius;
            width = rhs.width;
            height = rhs.height;
        }

        void updateRegion(Point2D location, float s)
        {
            //info
            max_response = max(max_response, s);
            strength+=s;
            center = center + location;
            size++;

            //bounding box
            if (location.x<rleft)
                rleft = location.x;
            else if (location.x>rright)
                rright = location.x;

            if (location.y<rtop)
                rtop = location.y;
            else if (location.y>rbottom)
                rbottom = location.y;
        }

        void finalizeRegion()
        {
            if(size>0.0)
            {
                strength/=size;
                center/=size;
                width = rright-rleft+1.0;
                height = rbottom - rtop + 1.0;
                radius = 0.5*max(width,height);//sqrt(width*width+height*height)/2.0;
            }
        }
    };
}

#endif // COMMON_FUNCTIONS_H
