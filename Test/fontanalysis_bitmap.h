#ifndef FONTANALYSISBITMAP_H
#define FONTANALYSISBITMAP_H

#include "test.h"

#include "../GSUB/gsub.h"
#include "../GSUB/LookupList/lookupsubtabletype1.h"
#include "../canvas.h"

class FontAnalysisBitmap : public Test
{
public:
    FontAnalysisBitmap();
    void print_feature(FontSeeker& fs, Canvas& canvas, Gsub& gsub, Feature& feature);
    void print_langsys(FontSeeker& fs, Canvas& canvas, Gsub& gsub, LangSys& langsys);
    void print_script(FontSeeker& fs, Canvas& canvas, Gsub& gsub, Script& script);
    void run();
};

#endif // FONTANALYSISBITMAP_H
