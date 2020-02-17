#include "image.hpp"

#include <iostream>
#include <fstream>

Image::Image( const int width , const int height ) : framebuffer(width * height) {
    this->width = width;
    this->height = height;
}

Image::~Image() {}

void Image::exportPPM() {
    std::ofstream ofs;
    ofs.open("./out.ppm");
    ofs << "P6" << std::endl << width << " " << height << std::endl << "255" << std::endl;
    for (int i = 0; i < width * height; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            ofs << (char)(255 * std::max(0.f, std::min(1.f , framebuffer[i][j]) ) );
        }
    }
    ofs.close();   
}

void Image::setPixel(const int x, const int y, Vec3f color) {
    for (int i = 0; i < 3; i++)
    {
        if(color[i] > 1.) 
            color[i] = 1.;
        
        if( color[i] < 0. )
            color[i] = 0.;
    }
    

    if( 0 <= x && x < width && 0 <= y && y < height )
        framebuffer[x + y * width] = color;
}

void Image::setBackground(Vec3f color) {
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            framebuffer[i + j * width] = color;
        }
    }
}

void Image::flip(const int type) {
   std::vector<Vec3f> framebuffer_tmp(width * height);

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            if ( type ==  HORIZONTAL_FLIP ) {
                framebuffer_tmp[ x + y * width ] = framebuffer[ ( width - 1 - x ) + ( y ) * width ];
            } else {
                framebuffer_tmp[ x + y * width ] = framebuffer[ x + (height - 1 - y ) * width ];
            }
        }
    }
    
    framebuffer = framebuffer_tmp;
}

Vec3f Image::getPixel(const int x, const int y) {
    if( 0 <= x && x < width && 0 <= y && y < height )
        return framebuffer[x + y * width];
    else 
        return Vec3f(0,0,0);
}