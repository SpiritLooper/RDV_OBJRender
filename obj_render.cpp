#include <iostream>
#include <fstream>
#include <limits>
#include "triangle.hpp"
#include "model.h"
#include "image.hpp"

const int width = 1024;
const int height = 768;
const int depth = 255;
Vec3f light_dir(0,0,-1);
Vec3f camera(0,0,3);

Matrix view2model(Vec3f v) {
    Matrix m(4,1);
    for (int i = 0; i < 3; i++)
    {
        m[i][0] = v[i];
    }
    m[3][0] = 1.;
    return m;
}

Vec3f model2view(Matrix m) {
    return Vec3f(int(m[0][0]/m[3][0] + 0.5), int(m[1][0]/m[3][0] + 0.5), m[2][0]/m[3][0]);
}

Matrix viewport(int x, int y, int w, int h) {
    Matrix m = Matrix::identity(4);
    m[0][3] = x+w/2.f;
    m[1][3] = y+h/2.f;
    m[2][3] = depth/2.f;

    m[0][0] = w/2.f;
    m[1][1] = h/2.f;
    m[2][2] = depth/2.f;
    return m;
}

void render(Model &model) {
   
    float zbuffer[width * height];
    
    for (int i = 0; i < width * height; i++)
    {
        zbuffer[i] = -std::numeric_limits<float>::max();
    }
    
    Image img(width , height);  

    std::cout << "Sorting triangle " ; 
    model.sort_faces();

    std::cout << "Drawing triangle " ; 

    Matrix ViewPort   = viewport(width/8, height/8, width*3/4, height*3/4);

    //Dessin des triangles du model
    for (int i = 0; i < model.nfaces() ; i++)
    {
        std::vector<int> face = model.face(i); 
        Vec3f screen_coords[3];
        Vec3f world_coords[3]; 
        for (int j=0; j<3; j++) { 
            Vec3f v = model.vert(face[j]); 
            screen_coords[j] = model2view(ViewPort * view2model(v));
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