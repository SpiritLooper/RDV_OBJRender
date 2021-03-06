#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <vector>
#include "geometry.h"

#define VERTICAL_FLIP 0
#define HORIZONTAL_FLIP 1

class Image {
private:
	std::vector<Vec3f> framebuffer;
    int width, height;
public:
	Image( const int w , const int h );
	~Image();
	void exportPPM();
    void setBackground(Vec3f color);
    void setPixel(const int pixel_x, const int pixel_y, Vec3f color);
    Vec3f getPixel(const int pixel_x, const int pixel_y);
    void flip(const int type);
    int get_width();
    int get_height();
    Image fusionner(Image& img);
};

#endif //__IMAGE_H__