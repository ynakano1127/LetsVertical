#ifndef CANVAS_H
#define CANVAS_H

#include <string>
#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "image.h"

class Canvas : public Image
{
private:
    int cur_x;
    int cur_y;
    int margin;
    int indent_size;
    int font_size;
    int dpi;
    FT_Library library;
    FT_Face face;
public:
    Canvas(std::string font_file_name, int w = 100, int h = 100, int margin = 10, int indent_size = 10, int font_size = 16, int dpi = 72);
    ~Canvas();
    void loadGlyph(FT_ULong glyph_index);
    void writeGlyph(int x, int y);
    void writeGlyphPair(FT_ULong left, FT_ULong right, int n=4);
    void writeGlyphPair(std::vector<FT_ULong> left, std::vector<FT_ULong> right, int n=4);
    void writeString(std::string s, int x, int y);
    void writeHeading(std::string heading, int n=0);
private:
    void setCurX(int cur_x);
    void setCurY(int cur_y);
};

#endif // CANVAS_H
