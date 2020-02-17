#include <iostream>
#include <fstream>
#include <limits>
#include "triangle.hpp"
#include "model.h"
#include "image.hpp"


void render(Model &model) {
    const int width = 1024;
    const int height = 768;

    const int delta = width * 0.05;

    Vec3f light_dir(0,0,-1);

    Image img(width , height);  

    std::cout << "Sorting triangle " ; 
    model.sort_faces();

    std::cout << "Drawing triangle " ; 

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

        Vec3f norm_triangle = (world_coords[2] - world_coords[0]) ^ (world_coords[1] - world_coords[0]);
        norm_triangle.normalize();
        float intensity = norm_triangle * light_dir;
        if(intensity > 0) {
            Vec2i screen_coords_delta_moins[3];
            Vec2i screen_coords_delta_plus[3];
            for (int i = 0; i < 3; i++)
            {
                screen_coords_delta_moins[i] = screen_coords[i];
                screen_coords_delta_plus[i] = screen_coords[i];
                screen_coords_delta_moins[i].x = screen_coords[i].x -  (delta / 2);
                screen_coords_delta_plus[i].x = screen_coords[i].x +  (delta / 2);
            }
            
            triangle(screen_coords_delta_moins, img, Vec3f(intensity, 0, 0));
            triangle(screen_coords_delta_plus, img, Vec3f(0, 0, intensity));
        }
    }
    
    std::cout << "\nFliping image ..." << std::endl; 
    img.flip(VERTICAL_FLIP);

    std::cout << "PPM exporting ..." << std::endl;
    img.exportPPM(); 

    std::cout << "Done" << std::endl;
}

int main(int argc, char const ** argv)
{
    std::string file_obj = "./model/duck.obj";
    
    if(argc == 2) {
       file_obj = std::string(argv[1]) ;
    }
    
    std::cout << "Loading model " << file_obj << std::endl;
    Model model(file_obj.c_str());
    
    render(model);
    
    return 0;
}