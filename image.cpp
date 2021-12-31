/*******************************
 * 画像 (8bit)
 *******************************/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "image.h"

//-------------

#define _MAKE_COL(r,g,b)   (((r) << 16) | ((g) << 8) | (b))

#define _GET_R(c)  ((uint8_t)((c) >> 16))
#define _GET_G(c)  ((uint8_t)((c) >> 8))
#define _GET_B(c)  ((uint8_t)(c))

//-------------



/* LE 2byte 出力 */

static void _write16(FILE *fp,uint16_t v)
{
	uint8_t b[2];

	b[0] = (uint8_t)v;
	b[1] = (uint8_t)(v >> 8);

	fwrite(b, 1, 2, fp);
}

/* LE 4byte 出力 */

static void _write32(FILE *fp,uint32_t v)
{
	uint8_t b[4];

	b[0] = (uint8_t)v;
	b[1] = (uint8_t)(v >> 8);
	b[2] = (uint8_t)(v >> 16);
	b[3] = (uint8_t)(v >> 24);

	fwrite(b, 1, 4, fp);
}

Image::Image(int width,int height) : width(width), height(height)
{
    buf = new uint32_t[height * width];
}

Image::~Image()
{
    delete[] buf;
}

Image::Image(const Image& image)
{
    if(&image == this){
        delete[] buf;
        width = 0;
        height = 0;
    }else{
        width = image.width;
        height = image.height;
        buf = new uint32_t[height * width];

        for(int h = 0; h < height; h++){
            for(int w = 0; w < width; w++){
                buf[h * width + w] = image.buf[h * width + w];
            }
        }
    }
}

Image& Image::operator=(const Image &image)
{
    if(&image != this){
        if (width!=image.width || height!=image.height) {
            delete[] buf;
            width = image.width;
            height = image.height;
            buf = new uint32_t[height * width];
        }
        for(int h = 0; h < height; h++){
            for(int w = 0; w < width; w++){
                buf[h * width + w] = image.buf[h * width + w];
            }
        }
    }
    return *this;
}

void Image::clear(uint32_t c)
{
    uint32_t *pd = buf;
	int i;

    for(i = width * height; i > 0; i--)
		*(pd++) = c;
}

void Image::drawHLine(int x, int y, int w, uint32_t c)
{
    for(; w > 0; w--)
        setPixel(x++, y, c);
}

void Image::drawVLine(int x,int y,int h,uint32_t c)
{
    for(; h > 0; h--)
        setPixel(x, y++, c);
}

void Image::fillBox(int x,int y,int w,int h,uint32_t c)
{
	int x2,y2,ix,iy,next;
	uint32_t *pd;

	x2 = x + w - 1;
	y2 = y + h - 1;

    if(x2 < 0 || y2 < 0 || x >= width || y >= height)
		return;

	if(x < 0) x = 0;
	if(y < 0) y = 0;
    if(x2 >= width) x2 = width - 1;
    if(y2 >= height) y2 = height - 1;

	//

    pd = buf + y * width + x;
    next = width - (x2 - x + 1);

	for(iy = y; iy <= y2; iy++)
	{
		for(ix = x; ix <= x2; ix++)
			*(pd++) = c;

		pd += next;
	}
}

void Image::setPixel(int x,int y,uint32_t c)
{
    if(x >= 0 && y >= 0 && x < width && y < height)
        *(buf + y * width + x) = c;
}

void Image::blendPixel(int x,int y,uint32_t c,int alpha)
{
	uint32_t *pd,dstc;
	uint8_t dr,dg,db,sr,sg,sb;

    if(x >= 0 && y >= 0 && x < width && y < height)
	{
        pd = buf + y * width + x;
		dstc = *pd;

		sr = _GET_R(c);
		sg = _GET_G(c);
		sb = _GET_B(c);

		dr = _GET_R(dstc);
		dg = _GET_G(dstc);
		db = _GET_B(dstc);

		//アルファ合成

		dr = (sr - dr) * alpha / 255 + dr;
		dg = (sg - dg) * alpha / 255 + dg;
		db = (sb - db) * alpha / 255 + db;

		*pd = _MAKE_COL(dr, dg, db);
	}
}

void Image::writeBitmap(const char *filename)
{
	FILE *fp;
	uint32_t *ps,c;
	uint8_t *buf,*pd;
	int ix,iy,imgsize,pitch;

	fp = fopen(filename, "wb");
	if(!fp) return;

    pitch = (width * 3 + 3) & (~3);
    imgsize = pitch * height;

	//1行用バッファ

	buf = (uint8_t *)malloc(pitch);
	if(!buf)
	{
		fclose(fp);
		return;
	}

	//ファイルヘッダ

	fputs("BM", fp);
	_write32(fp, 14 + 40 + imgsize);
	_write32(fp, 0);
	_write32(fp, 14 + 40);

	//情報ヘッダ

	_write32(fp, 40);
    _write32(fp, width);
    _write32(fp, height);
	_write16(fp, 1);
	_write16(fp, 24);
	_write32(fp, 0);
	_write32(fp, imgsize);
	_write32(fp, 3780);
	_write32(fp, 3780);
	_write32(fp, 0);
	_write32(fp, 0);

	//イメージ (ボトムアップ)

    ps = this->buf + (height - 1) * width;

    for(iy = height; iy > 0; iy--)
	{
		pd = buf;
		
        for(ix = width; ix > 0; ix--, pd += 3)
		{
			c = *(ps++);

			pd[0] = _GET_B(c);
			pd[1] = _GET_G(c);
			pd[2] = _GET_R(c);
		}
		
		fwrite(buf, 1, pitch, fp);

        ps -= width * 2;
	}

	//

	fclose(fp);

	free(buf);
}

