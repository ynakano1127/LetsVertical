#include "canvas.h"

Canvas::Canvas(std::string font_file_name, int w, int h, int margin, int indent_size, int font_size, int dpi)
    : Image(w, h), cur_x(margin), cur_y(margin), margin(margin), indent_size(indent_size), font_size(font_size), dpi(dpi)
{
    clear(0xffffff);

    FT_Error error = FT_Init_FreeType(&library);
    if(error)
        throw "something error occured at FT_Init_FreeType";

    error = FT_New_Face(
                library,
                font_file_name.c_str(),
                0,
                &face
    );
    if(error)
        throw "something error occured at FT_New_Face";

    error = FT_Set_Char_Size(
        face,
        0,
        font_size * 64,
        dpi,
        dpi);
    if(error)
        throw "something error occured at FT_Set_Char_Size";
}

Canvas::~Canvas()
{

}

void Canvas::loadGlyph(FT_ULong glyph_index)
{
    FT_Error error = FT_Load_Glyph(
        face,
        glyph_index,
        FT_LOAD_DEFAULT);
    if (error)
        throw "something error occured at FT_Load_Glyph";

    error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
    if (error)
        throw "something error occured at FT_Render_Glyph";
}

void Canvas::writeGlyph(int x, int y)
{
    unsigned int height = face->glyph->bitmap.rows;
    unsigned int width = face->glyph->bitmap.width;
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            uint32_t gray_color = face->glyph->bitmap.buffer[h * width + w];
            gray_color = 255 - gray_color;
            uint32_t color = (gray_color << 16) + (gray_color << 8) + gray_color;
            setPixel(
                        x + w + face->glyph->metrics.horiBearingX/64,
                        y + h - face->glyph->metrics.horiBearingY/64,
                        color);
        }
    }
}

void Canvas::writeGlyphPair(FT_ULong left, FT_ULong right, int n)
{
    int font_dot_size = (double)font_size/72.0 * dpi ;
    int indent = margin + indent_size * n;

    if(cur_x < indent)
        setCurX(indent);

    if(cur_x + margin * 3 + font_dot_size * 2 > getWidth()){
        setCurX(margin + indent_size * n);
        setCurY(cur_y + font_dot_size + margin);
    }
    setCurX(cur_x + margin);
    loadGlyph(left);
    writeGlyph(cur_x, cur_y);

    setCurX(cur_x + margin + font_dot_size);
    loadGlyph(right);
    writeGlyph(cur_x, cur_y);

    setCurX(cur_x + margin + font_dot_size);
    drawVLine(cur_x, cur_y - face->glyph->metrics.horiBearingY/64, font_dot_size, 0x000000);
}

void Canvas::writeGlyphPair(std::vector<FT_ULong> left, std::vector<FT_ULong> right, int n)
{

}

void Canvas::writeString(std::string s, int x, int y)
{
    for(int i=0;i<s.size();i++){
        FT_ULong glyph_index = FT_Get_Char_Index(face, s[i]);
        loadGlyph(glyph_index);
        writeGlyph(x, y);
        x += face->glyph->metrics.horiAdvance/64;
    }
}

void Canvas::writeHeading(std::string heading, int n)
{
    setCurX(margin + indent_size * n);
    setCurY(cur_y + (double)font_size/72.0 * dpi + margin);
    writeString(heading, cur_x,  cur_y);
}

void Canvas::setCurX(int cur_x)
{
    this->cur_x = cur_x;
}

void Canvas::setCurY(int cur_y)
{
    int font_dot_size = (double)font_size/72.0 * dpi ;

    this->cur_y = cur_y;
    if(cur_y + font_dot_size > getHeight())
        expand(1000);
}
