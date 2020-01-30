#ifndef TRIANGLE
#define TRIANGLE

#include <vector>
#include <cmath>
#include "geometry.h"


struct Line {
    int x1, y1, x2, y2;
    Vec3f color;
    
    void draw( std::vector<Vec3f> &framebuffer, const int width, const int height ) {
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
            if( 0 <= x && x < width && 0 <= y && y < height ) {
                if(steep) {
                    framebuffer[ y + x * width] = color;
                } else {
                    framebuffer[ x + y * width] = color;
                }
            }
            error += derror;
            if ( error > dx) {
                y += ( y2 > y1 ? 1 : -1); 
                error -= dx * 2;
            }
        }
        
    }
};

#endif