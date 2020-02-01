#ifndef TRIANGLE
#define TRIANGLE

#include <vector>
#include <cmath>
#include "geometry.h"
#include "image.hpp"

struct Line {
    int x1, y1, x2, y2;
    Vec3f color;
    
    void draw( Image &img ) {
        int dx , dy , x , y;
        int derror, error;

        bool steep = false;
        if( std::abs(x1 - x2) < std::abs(y1 - y2)) {
            std::swap(x1, y1);
            std::swap(x2, y2);
            steep = true;
        }

        if( x1 > x2 ) {
            std::swap(x1, x2);
            std::swap(y1, y2);
        }

        dx = x2 - x1;
        dy = y2 - y1;
        y = y1;
        error = 0;
        derror = std::abs(dy) * 2;
        
        for ( x = x1; x  <= x2 ; x++)
        {
            if(steep) {
                img.setPixel(y,x, color);
            } else {
                img.setPixel(x,y, color);
            }
        
            error += derror;
            if ( error > dx) {
                y += ( y2 > y1 ? 1 : -1); 
                error -= dx * 2;
            }
        }
        
    }
};

void triangle(Vec2i * pts ,  Image &img, Vec3f color) {
    for (int i = 0; i < 3; i++)
    {
        Line line = { pts[i].x , pts[i].y , pts[ ( i+1 ) % 3].x, pts[ ( i+1 ) % 3].y, color  };
        line.draw(img);
    }
}

#endif