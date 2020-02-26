#include "camera.hpp"

const int depth = 255;
const float ecart_analygraphe = 0.25;

Camera::Camera(Vec3f position, Image i, int m) : eye(position), mode(m) {
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

    center = Vec3f(0, 0, 0);
    up = Vec3f(0, 1, 0);
};

Vec3f Camera::m2v(Matrix m) {
    return Vec3f(int(m[0][0]/m[3][0] + 0.5), int(m[1][0]/m[3][0] + 0.5), m[2][0]/m[3][0]);
};

Matrix Camera::translate(float x, float y , float z) {
    Matrix R = Matrix::identity(4);

    R[0][3] = x;
    R[1][3] = y;
    R[2][3] = z;

    return R;
}

Matrix Camera::v2m(Vec3f v) {
    Matrix m(4,1);
    for (int i = 0; i < 3; i++)
    {
        m[i][0] = v[i];
    }
    m[3][0] = 1.;
    return m;
};

Matrix Camera::lookat() {
    Vec3f z = (eye-center).normalize();
    Vec3f x = (up^z).normalize();
    Vec3f y = (z^x).normalize();
    Matrix res = Matrix::identity(4);
    for (int i=0; i<3; i++) {
        res[0][i] = x[i];
        res[1][i] = y[i];
        res[2][i] = z[i];
        res[i][3] = -center[i];
    }
    return res;
}

Vec3f Camera::camera_transform(Vec3f p) {
    Matrix res = ViewPort;
    Matrix ModelView = lookat();

    if (mode == PERSPECTIVE)
    {
        res = res * Projection;
    }

    return m2v(res * ModelView * v2m(p));
}

void Camera::camera_transform_analygraph(Vec3f p, Vec3f& le, Vec3f& re) {
    Matrix res = ViewPort;

    if (mode == PERSPECTIVE)
    {
        res = res * Projection;
    }
    
    Matrix trans_left =  translate(- ( ecart_analygraphe / 2.f),0 ,0);
    Matrix trans_right = translate(    ecart_analygraphe / 2.f ,0 ,0);

    Matrix ModelView = lookat();

    Matrix ModelViewLeft  = ModelView * trans_left;
    Matrix ModelViewRight = ModelView * trans_right;

    le = m2v(res * ModelViewLeft  * v2m(p));
    re = m2v(res * ModelViewRight * v2m(p));
}