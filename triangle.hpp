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

Vec3f barycentric(Vec3f A, Vec3f B, Vec3f C, Vec3f P) {
    Vec3f s[2];
    for (int i=2; i--; ) {
        s[i][0] = C[i]-A[i];
        s[i][1] = B[i]-A[i];
        s[i][2] = A[i]-P[i];
    }
    Vec3f u = s[0] ^ s[1];
    if (std::abs(u[2])>1e-2) 
        return Vec3f(1.f-(u.x+u.y)/u.z, u.y/u.z, u.x/u.z);
    return Vec3f(-1,1,1);
}

void triangle(Vec3f *pts, float *zbuffer, Image &image, Vec3f color) {
    Vec2f bboxmin( std::numeric_limits<float>::max(),  std::numeric_limits<float>::max());
    Vec2f bboxmax(-std::numeric_limits<float>::max(), -std::numeric_limits<float>::max());
    Vec2f clamp(image.get_width()-1, image.get_height()-1);
    
    for (int i=0; i<3; i++) {
        for (int j=0; j<2; j++) {
            bboxmin[j] = std::max(0.f,      std::min(bboxmin[j], pts[i][j]));
            bboxmax[j] = std::min(clamp[j], std::max(bboxmax[j], pts[i][j]));
        }
    }
    
    Vec3f P;
    
    for (P.x=bboxmin.x; P.x<=bboxmax.x; P.x++) {
        for (P.y=bboxmin.y; P.y<=bboxmax.y; P.y++) {
            Vec3f bc_screen  = barycentric(pts[0], pts[1], pts[2], P);
            if (bc_screen.x<0 || bc_screen.y<0 || bc_screen.z<0) continue;
            P.z = 0;
            for (int i=0; i<3; i++) P.z += pts[i][2]*bc_screen[i];
            if (zbuffer[int(P.x+P.y*image.get_width())]<P.z) {
                zbuffer[int(P.x+P.y*image.get_width())] = P.z;
                image.setPixel(P.x, P.y, color);
            }
        }
    }
}


#endif