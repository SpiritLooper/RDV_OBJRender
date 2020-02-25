#include "camera.hpp"

const int depth = 255;

Camera::Camera(Vec3f position, Image i, int m) : pos(position), mode(m) {
    ViewPort = Matrix::identity(4);
    
    int x , y , h, w;
    x = i.get_width()  / 8;
    y = i.get_height() / 8;
    w = i.get_width()  * 3/4;
    h = i.get_height() * 3/4;

    ViewPort[0][3] = x+w/2.f;
    ViewPort[1][3] = y+h/2.f;
    ViewPort[2][3] = depth/2.f;
    
    ViewPort[0][0] = w/2.f;
    ViewPort[1][1] = h/2.f;
    ViewPort[2][2] = depth/2.f;

    Projection = Matrix::identity(4);
    Projection[3][2] = -1.f/position.z;
};

Vec3f Camera::m2v(Matrix m) {
    return Vec3f(int(m[0][0]/m[3][0] + 0.5), int(m[1][0]/m[3][0] + 0.5), m[2][0]/m[3][0]);
};

Matrix Camera::v2m(Vec3f v) {
    Matrix m(4,1);
    for (int i = 0; i < 3; i++)
    {
        m[i][0] = v[i];
    }
    m[3][0] = 1.;
    return m;
};

Vec3f Camera::camera_transform(Vec3f p) {
    Matrix res = ViewPort;

    if (mode == PERSPECTIVE)
    {
        res = res * Projection;
    }

    return m2v(res * v2m(p));
}