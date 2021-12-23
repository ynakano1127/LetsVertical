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
    Image(int w, int h);
    ~Image();
//    void Image_free(Image *p);
//    Image *Image_new(int width,int height);

    void clear(uint32_t c);
//    void Image_drawHLine(Image *p,int x,int y,int w,uint32_t c);
//    void Image_drawVLine(Image *p,int x,int y,int h,uint32_t c);
    void fillBox(int x,int y,int w,int h,uint32_t c);

    void setPixel(int x,int y,uint32_t c);
    void blendPixel(int x,int y,uint32_t c,int alpha);

    void writeBitmap(const char *filename);
};

#endif // IMAGE_H
