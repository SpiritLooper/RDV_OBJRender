#ifndef CAMERA
#define CAMERA

#include "geometry.h"
#include "matrix.hpp"
#include "image.hpp"

#define ORTOGRAPHIC 0
#define PERSPECTIVE 1

class Camera {
    private:
        Vec3f eye;
        Vec3f center;
        Vec3f up;
        Matrix ViewPort;
        Matrix Projection;
        int mode;

        Vec3f  m2v(Matrix m);
        Matrix v2m(Vec3f m);
        Matrix lookat();
        Matrix translate(float x, float y , float z);
        
    public:
        Camera(Vec3f pos, Image render, int mode);
        Vec3f camera_transform(Vec3f world_point);
        void camera_transform_analygraph(Vec3f world_point, Vec3f& left_eye, Vec3f& right_eye);

};


#endif