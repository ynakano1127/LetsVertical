#include <iostream>
#include "writetest.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#define FLAG_NUMBER 16

#include "../image.h"
#include "../GSUB/gsub.h"
#include "../GSUB/LookupList/lookupsubtabletype1.h"

using namespace std;

char *flag_names[FLAG_NUMBER] = {
    "FT_FACE_FLAG_SCALABLE",
    "FT_FACE_FLAG_FIXED_SIZES",
    "FT_FACE_FLAG_FIXED_WIDTH",
    "FT_FACE_FLAG_SFNT",
    "FT_FACE_FLAG_HORIZONTAL",
    "FT_FACE_FLAG_VERTICAL",
    "FT_FACE_FLAG_KERNING",
    "FT_FACE_FLAG_FAST_GLYPHS",
    "FT_FACE_FLAG_MULTIPLE_MASTERS",
    "FT_FACE_FLAG_GLYPH_NAMES",
    "FT_FACE_FLAG_EXTERNAL_STREAM ",
    "FT_FACE_FLAG_HINTER",
    "FT_FACE_FLAG_CID_KEYED",
    "FT_FACE_FLAG_TRICKY",
    "FT_FACE_FLAG_COLOR",
    "FT_FACE_FLAG_VARIATION",
};

FT_Long unicodes[] = {
    0x300C, //「
    0x30AD, //キ
    0x30EA, //リ
    0x30C8, //ト
    0x304B, //か
    0x306A, //な
    0x3041, //ぁ
    0x3001, //、
    0x3084, //や
    0x3063, //っ
    0x3071, //ぱ
    0x2012, //dash
    0x2013, //dash
    0x2014, //dash
    0x2015, //dash
    0x2053, //dash
    0x2E3A, //dash
    0x301C, //dash
    0x3030, //dash
    0x2010, //hyphen
    0x002D, //hyphen
    0x00AD, //hyphen
    0x2011, //hyphen
    0x2043, //hyphen
};

//FT_Long unicodes[] = {
//    0x300C,
//    0x4FFA,
//    0x306F,
//    0xFF72,
//    0xFF74,
//    0xFF7D,
//    0xFF72,
//    0xFF77,
//    0xFF98,
//    0xFF84,
//    0x0021,
//    0xFF01,
//    0x300D,
//};

//FT_Long unicodes[] = {
//    0x3042,
//    0x3041,
//    0x3041,
//    0x2026,
//    0x3084,
//    0x3063,
//    0x3061,
//    0x307E,
//    0x3063,
//    0x305F,
//    0x301C
//};

WriteTest::WriteTest()
{

}

void render(Image &img, FT_GlyphSlot slot, int x, int y) {
    unsigned int height = slot->bitmap.rows;
    unsigned int width = slot->bitmap.width;
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            uint32_t gray_color = slot->bitmap.buffer[h * width + w];
            gray_color = 255 - gray_color;
            uint32_t color = (gray_color << 16) + (gray_color << 8) + gray_color;
            img.setPixel(x + w, y + h, color);
        }
    }
}

void load_char(FT_Face face, FT_GlyphSlot slot, FT_Long unicode, vector<LookupSubtableType1> lst1_list = vector<LookupSubtableType1>())
{
    FT_ULong glyph_index = FT_Get_Char_Index(face, unicode);

    for(auto l : lst1_list)
        glyph_index = l.convertGlyph(glyph_index);

    FT_Error error = FT_Load_Glyph(
        face,             /* handle to face object */
        glyph_index,      /* glyph index           */
        FT_LOAD_DEFAULT); /* load flags, see below */
    if (error)
    {
        printf("something error occured\n at FT_Load_Glyph");
    }

    error = FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL);
    if (error)
    {
        printf("something error occured\n at FT_Render_Glyph");
    }
}

vector<LookupSubtableType1> getLST1() {
    FontSeeker fs("NotoSerifJP-Regular.otf");
    Gsub gsub(fs);

    Script script;
    for(auto script_record : gsub.getScriptList().getScriptList()){
        cout << "ScriptRecord Tag : " << script_record.getScriptTag().toString() << endl;
        if(script_record.getScriptTag().toString() == "kana")
            script = script_record.getScript();
    }

    LangSys langsys;
    langsys = script.getDefaultLangSys();
    for(auto lang_sys_record : script.getLangSysList()) {
        cout << "LangSysRecord Tag : " << lang_sys_record.getLangSysTag().toString() << endl;
        if(lang_sys_record.getLangSysTag().toString() == "JAN ")
            langsys = lang_sys_record.getLangSys();
    }

    Feature feature;
    vector<FeatureRecord> feature_records = gsub.getFeatureList().getFeatureList();
    for(uint16_t i : langsys.getFeatureIndices()){
        FeatureRecord r = feature_records[i];
        cout << "FeatureRecord Tag : " << r.getFeatureTag().toString() << endl;
        if( r.getFeatureTag().toString() == "vrt2")
            feature = r.getFeature();
    }

    vector<LookupSubtableType1> lst1_list;
    vector<Lookup> lookups = gsub.getLookupList().getLookupList();
    for(uint16_t i : feature.getLookupListIndices()){
        Lookup l = lookups[i];
        cout << "Lookup Type : " << l.getLookupType() << endl;
        if(l.getLookupType() == 1)
            for(uint16_t offset : l.getSubtableOffsets())
                lst1_list.push_back(LookupSubtableType1(fs, l.getLookupOffset() + offset));
    }
    return lst1_list;
}

void WriteTest::run()
{
//    開始処理
    Image img(1000,1000);
    img.clear(0xffffff);
    vector<LookupSubtableType1> lst1_list = getLST1();
//    開始処理終わり


    FT_Library library;

    FT_Error error = FT_Init_FreeType(&library);
    if (error)
        printf("something error occured\n at FT_Init_FreeType");

    FT_Face face;

    error = FT_New_Face(
        library,
        "NotoSerifJP-Regular.otf",
        0,
        &face);
    if (error)
        printf("something error occured\n at FT_New_Face");

    // 情報出力
    printf("face->num_glyphs = %li\n", face->num_glyphs);
    printf("face->face_flags = %li\n", face->face_flags);
    for (int i = 0; i < FLAG_NUMBER; i++)
    {
        printf("flags : %s = %li\n", flag_names[i], (face->face_flags >> i) & 1);
    }
    printf("face->units_per_EM = %d\n", face->units_per_EM);
    printf("face->num_fixed_sizes = %d\n", face->num_fixed_sizes);
    printf("face->available_sizes pointer = %p\n", face->available_sizes);
    for (int i = 0; i < face->num_fixed_sizes; i++)
    {
        FT_Bitmap_Size size = (face->available_sizes)[i];
        printf("i = %d, height = %d, width = %d\n", i, size.height, size.width);
    }
    // 情報出力終わり

    error = FT_Set_Char_Size(
        face,    /* handle to face object           */
        0,       /* char_width in 1/64th of points  */
        16 * 64, /* char_height in 1/64th of points */
        180,     /* horizontal device resolution    */
        180);    /* vertical device resolution      */
    if (error)
        printf("something error occured\n at FT_Set_Char_Size");

    FT_GlyphSlot slot;
    slot = face->glyph;
    int point_x = 950, point_y = 20;
    for (auto code : unicodes)
    {
        load_char(face, slot, code, lst1_list);
        render(img, slot,
               point_x + face->glyph->metrics.vertBearingX/64,
               point_y + face->glyph->metrics.vertBearingY/64);
        point_y += face->glyph->metrics.vertAdvance/64;
    }


//    終了処理
    char title[32];
    snprintf(title, 32, "output.bmp");
    img.writeBitmap(title);
//    終了処理終わり
}
