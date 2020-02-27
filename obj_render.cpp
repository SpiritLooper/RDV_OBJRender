#include <iostream>
#include <fstream>
#include <limits>
#include "triangle.hpp"
#include "model.h"
#include "image.hpp"
#include "camera.hpp"

const int width = 1024;
const int height = 768;

Vec3f light_dir(0,0,-1);
Vec3f camera_pos(2,1,3);

void render(Model* model, bool _3D) {
   
    float* zbuffer = new float[width * height];
    float* zbuffer_red = new float[width * height];
    float* zbuffer_blue = new float[width * height];
    
    for (int i = 0; i < width * height; i++)
    {
        zbuffer[i] = -std::numeric_limits<float>::max();
        zbuffer_blue[i] = -std::numeric_limits<float>::max();
        zbuffer_red[i] = -std::numeric_limits<float>::max();
    }
    
    Image img(width , height);  
    Image img_red(width , height);  
    Image img_blue(width , height);  

    Camera cam(camera_pos, img, PERSPECTIVE);

    std::cout << "Drawing triangle " ; 

    //Dessin des triangles du model
    for (int i = 0; i < model->nfaces() ; i++)
    {
        std::vector<int> face = model->face(i); 
        Vec3f screen_coords[3];
        Vec3f world_coords[3]; 

        Vec3f screen_coords_left_eye[3];
        Vec3f screen_coords_right_eye[3];

        for (int j=0; j<3; j++) { 
            Vec3f v = model->vert(face[j]); 
            screen_coords[j] = cam.camera_transform(v);

            cam.camera_transform_analygraph(v, screen_coords_left_eye[j], screen_coords_right_eye[j] );

            world_coords[j]  = v; 
        }

        Vec3f norm_triangle = (world_coords[2] - world_coords[0]) ^ (world_coords[1] - world_coords[0]);
        norm_triangle.normalize();
        float intensity = norm_triangle * light_dir;
        
        if(_3D) {
            triangle(screen_coords_left_eye,  zbuffer_red, img_red, Vec3f(intensity, 0, 0));
            triangle(screen_coords_right_eye, zbuffer_blue, img_blue, Vec3f(0, 0, intensity));
        } else {
            triangle(screen_coords, zbuffer, img, Vec3f(intensity, intensity, intensity));
        }
        
    }
    if(_3D) 
        img = img_red.fusionner(img_blue);

    std::cout << "\nFliping image ..." << std::endl; 
    img.flip(VERTICAL_FLIP);

    std::cout << "PPM exporting ..." << std::endl;
    img.exportPPM(); 

    std::cout << "Done" << std::endl;
}

int main(int argc, char const ** argv)
{
    std::string file_obj = "./model/head.obj";
    
    bool _3Dmode = true;

    if(argc >= 2) {
        for (int i = 1; i <= 2 && i < argc; i++)
        {
            if ( std::string(argv[i]) == "--no-3d" ){
                _3Dmode = false;
                std::cout << "*** Disabled 3D ***"  << std::endl;

            } else {
                file_obj = std::string(argv[i]) ;
            }
        }
    }
    
    std::cout << "Loading model " << file_obj << std::endl;
    Model* model = new Model(file_obj.c_str());
    
    render(model, _3Dmode);
    
    return 0;
}