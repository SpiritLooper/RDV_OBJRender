#include <iostream>
#include <fstream>
#include <limits>
#include "triangle.hpp"
#include "model.h"

void render(Model &model) {
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

    for (int i = 0; i < model.nfaces() ; i++)
    {
        std::vector<int> face = model.face(i);
        for (size_t j = 0; j < 3; j++)
        {
            Vec3f v0 = model.vert(face[j]);
            Vec3f v1 = model.vert(face[ (j + 1) % 3]);
            int x1 = (v0.x + 1.) * width / 2.;
            int y1 = (v0.y + 1.) * height / 2.;
            int x2 = (v1.x + 1.) * width / 2.;
            int y2 = (v1.y + 1.) * height / 2.;
            Line line = { x1, y1, x2, y2 , Vec3f(1., 1. ,1.) };
            line.draw(framebuffer, width, height);
        }
    }
    
    
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
    Model model("./model/head.obj");
    if(argc == 2) {
        model = Model(argv[1]);
    }
    
    render(model);
    return 0;
}