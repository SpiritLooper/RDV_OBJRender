#include <iostream>
#include <fstream>
#include <limits>
#include "triangle.hpp"
#include "model.h"
#include "image.hpp"


void render(Model &model) {
    const int width = 1024;
    const int height = 768;

    Vec3f light_dir(0,0,-1);

    float zbuffer[width * height];
    
    for (int i = 0; i < width * height; i++)
    {
        zbuffer[i] = -std::numeric_limits<float>::max();
    }
    

    Image img(width , height);  

    std::cout << "Sorting triangle " ; 
    model.sort_faces();

    std::cout << "Drawing triangle " ; 

    //Dessin des triangles du model
    for (int i = 0; i < model.nfaces() ; i++)
    {
        std::vector<int> face = model.face(i); 
        Vec3f screen_coords[3];
        Vec3f world_coords[3]; 
        for (int j=0; j<3; j++) { 
            Vec3f v = model.vert(face[j]); 
            screen_coords[j] = Vec3f(int((v.x+1.)*width/2. + .5), int((v.y+1.)*height/2.+.5), v.z); 
            world_coords[j]  = v; 
        }

        Vec3f norm_triangle = (world_coords[2] - world_coords[0]) ^ (world_coords[1] - world_coords[0]);
        norm_triangle.normalize();
        float intensity = norm_triangle * light_dir;
        if(intensity > 0) {
            triangle(screen_coords, zbuffer, img, Vec3f(intensity, intensity, intensity));
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