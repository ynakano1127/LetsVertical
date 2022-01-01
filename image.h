#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>

class Image
{
private:
	uint32_t *buf;
	int width,
		height;
public:
    Image(int w = 100, int h = 100);
    ~Image();
    Image(const Image& image);
    Image& operator=(const Image& image);
    void clear(uint32_t c);
    void drawHLine(int x,int y,int w,uint32_t c);
    void drawVLine(int x,int y,int h,uint32_t c);
    void fillBox(int x,int y,int w,int h,uint32_t c);
    void setPixel(int x,int y,uint32_t c);
    void blendPixel(int x,int y,uint32_t c,int alpha);
    void expand(int size, bool x_axis = false, uint32_t c = 0xffffff);
    void writeBitmap(const char *filename);
    int getWidth() { return width; };
    int getHeight() { return height; };
};

#endif // IMAGE_H
