#include <iostream>
#include <fstream>
#include <cmath>
#include <limits>
#include <vector>
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


void render(Line &l) {
    const int width = 1024;
    const int height = 768;

    std::vector<Vec3f> framebuffer(width * height);

    // Dessin du fond
    for (size_t j = 0; j < height; j++)
    {
        for (size_t i = 0; i < width; i++)
        {
            framebuffer[i + j * width] = Vec3f( 0.2 , 0.2, 0.2 );
        }
    }

    // Dessin de la ligne
    l.draw(framebuffer,width, height);
    
    // Rendu en image
    std::ofstream ofs;
    ofs.open("./out.ppm");
    ofs << "P6" << std::endl << width << " " << height << std::endl << "255" << std::endl;
    for (size_t i = 0; i < width * height; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            ofs << (char)(255 * std::max(0.f, std::min(1.f , framebuffer[i][j]) ) );
        }
    }
    ofs.close();   
}

int main(int argc, char const *argv[])
{
    Line line = { 500 , 458 , 25, 25 ,  Vec3f(.12, 1 , .45) };
    render(line);
    return 0;
}