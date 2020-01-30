#include <iostream>
#include <fstream>
#include <cmath>
#include <limits>
#include <vector>
#include "geometry.h"

void render() {
    const int width = 1024;
    const int height = 768;

    std::vector<Vec3f> framebuffer(width * height);

    for (size_t j = 0; j < height; j++)
    {
        for (size_t i = 0; i < width; i++)
        {
            framebuffer[i + j * width] = Vec3f( 0 , float(i) /float(width) ,  float(j)  / float(height) );
        }
    }
    
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
    render();
    return 0;
}