#include <iostream>
#include <fstream>
#include <limits>
#include "triangle.hpp"
#include "model.h"
#include "image.hpp"

void render(Model &model) {
    const int width = 1024;
    const int height = 768;

    Image img(width , height);

    Vec3f min, max;

    model.get_bbox(min,max);

    //Dessin des triangles du model
    for (int i = 0; i < model.nfaces() ; i++)
    {
        std::vector<int> face = model.face(i); 
        Vec2i screen_coords[3];
        Vec3f world_coords[3]; 
        for (int j=0; j<3; j++) { 
            Vec3f v = model.vert(face[j]); 
            screen_coords[j] = Vec2i((v.x+1.)*width/2., (v.y+1.)*height/2.); 
            world_coords[j]  = v; 
        }    
        triangle(screen_coords, img, Vec3f(1.,1.,1.));
    }
    
    img.flip(HORIZONTAL_FLIP);

    img.exportPPM(); 
}

int main(int argc, char const ** argv)
{
    std::string file_obj = "./model/duck.obj";
    
    if(argc == 2) {
       file_obj = std::string(argv[1]) ;
    }
   
    Model model(file_obj.c_str());
    
    render(model);
    return 0;
}