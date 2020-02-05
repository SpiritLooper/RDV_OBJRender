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
    
    if(pts[0].y > pts[1].y ) std::swap(pts[0], pts[1]);
    if(pts[0].y > pts[2].y ) std::swap(pts[0], pts[2]);
    if(pts[1].y > pts[2].y ) std::swap(pts[1], pts[2]);

    int total_height = pts[2].y - pts[0].y;

    // Partie hausse du triangle
    for (int y = pts[0].y; y <= pts[1].y; y++)
    {
        int segment_height = pts[1].y - pts[0].y + 1 ;
        float alpha = (float)(y - pts[0].y)/total_height;
        float beta = (float)(y - pts[0].y)/segment_height;
        Vec2i A = pts[0] + (pts[2] - pts[0]) * alpha;
        Vec2i B = pts[0] + (pts[1] - pts[0]) * beta;
        if ( A.x > B.x ) std::swap(A, B);
        for ( int j = A.x ; j <= B.x ; j++ ) {
            img.setPixel(j, y , color );
        }
    }
    
    // Partie basse du triangle
    for (int y = pts[1].y; y <= pts[2].y; y++)
    {
        int segment_height = pts[2].y - pts[1].y + 1;
        float alpha = (float)(y - pts[0].y)/total_height;
        float beta = (float)(y - pts[1].y)/segment_height;
        Vec2i A = pts[0] + (pts[2] - pts[0]) * alpha;
        Vec2i B = pts[1] + (pts[2] - pts[1]) * beta;
        if ( A.x > B.x ) std::swap(A, B);
        for ( int j = A.x ; j <= B.x ; j++ ) {
            img.setPixel(j, y , color );
        }
    }
}

#endif