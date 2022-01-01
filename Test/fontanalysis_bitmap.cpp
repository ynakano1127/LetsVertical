#include <iostream>

#include "fontanalysis_bitmap.h"

using namespace std;

//string fonts2[] = {
//    "HinaMincho-Regular.ttf",
//    "KaiseiDecol-Regular.ttf",
//    "KaiseiHarunoUmi-Regular.ttf",
////    "KaiseiOpti-Regular.ttf",
////    "KaiseiTokumin-Regular.ttf",
////    "KiwiMaru-Regular.ttf",
//    "NewTegomin-Regular.ttf",
////    "NotoSerifJP-Regular.otf",
////    "ShipporiMinchoB1-Regular.ttf",
////    "ShipporiMincho-Regular.ttf",
//    "YujiBoku-Regular.ttf",
////    "YujiMai-Regular.ttf",
////    "YujiSyuku-Regular.ttf",
//    "ZenAntique-Regular.ttf",
//    "ZenAntiqueSoft-Regular.ttf",
//    "ZenOldMincho-Regular.ttf"
//};


string fonts2[] = {
    "HinaMincho-Regular.ttf",
    "KaiseiDecol-Regular.ttf",
    "KaiseiHarunoUmi-Regular.ttf",
    "KaiseiOpti-Regular.ttf",
    "KaiseiTokumin-Regular.ttf",
    "KiwiMaru-Regular.ttf",
    "NewTegomin-Regular.ttf",
    "NotoSerifJP-Regular.otf",
    "ShipporiMinchoB1-Regular.ttf",
    "ShipporiMincho-Regular.ttf",
    "YujiBoku-Regular.ttf",
    "YujiMai-Regular.ttf",
    "YujiSyuku-Regular.ttf",
    "ZenAntique-Regular.ttf",
    "ZenAntiqueSoft-Regular.ttf",
    "ZenOldMincho-Regular.ttf"
};

FontAnalysisBitmap::FontAnalysisBitmap()
{

}

void FontAnalysisBitmap::print_feature(FontSeeker& fs, Canvas& canvas, Gsub& gsub, Feature& feature) {
    Lookup lookup;

    vector<Lookup> lookups = gsub.getLookupList().getLookupList();
    for(uint16_t i : feature.getLookupListIndices()){
        lookup = lookups[i];
        canvas.writeHeading(to_string(lookup.getLookupType()), 3);
        if(lookup.getLookupType() == 1){
            for(uint16_t offset : lookup.getSubtableOffsets()){
                LookupSubtableType1 lst1(fs, lookup.getLookupOffset() + offset);
                Coverage coverage = lst1.getCoverage();
                for(const auto &item: coverage.getCoverageMap()){
                    canvas.writeGlyphPair(item.first, lst1.convertGlyph(item.first) );
                }
            }
        }
    }
}

void FontAnalysisBitmap::print_langsys(FontSeeker& fs, Canvas& canvas, Gsub& gsub, LangSys& langsys) {
    Feature feature;

    vector<FeatureRecord> feature_records = gsub.getFeatureList().getFeatureList();
    for(uint16_t i : langsys.getFeatureIndices()){
        FeatureRecord r = feature_records[i];
        canvas.writeHeading(r.getFeatureTag().toString(), 2);
        Feature feature = r.getFeature();
        print_feature(fs, canvas, gsub, feature);
    }
}

void FontAnalysisBitmap::print_script(FontSeeker& fs, Canvas& canvas, Gsub& gsub, Script& script) {
    LangSys langsys;

    canvas.writeHeading("DefaultLangSys", 1);
    langsys = script.getDefaultLangSys();
    print_langsys(fs, canvas, gsub, langsys);

    for(auto lang_sys_record : script.getLangSysList()) {
        canvas.writeHeading(lang_sys_record.getLangSysTag().toString(), 1);
        langsys = lang_sys_record.getLangSys();
        print_langsys(fs, canvas, gsub, langsys);
    }
}

void FontAnalysisBitmap::run() {
    for(string filename : fonts2){
        Canvas canvas(filename, 1000, 1000, 10, 50, 16, 120);
        canvas.writeBitmap((filename + "_analysis.bmp").c_str());

        FontSeeker fs(filename);
        Gsub gsub(fs);
        Script script;

        for(auto script_record : gsub.getScriptList().getScriptList()){
            string tag = script_record.getScriptTag().toString();
            if(!(tag=="DFLT" || tag=="hani" || tag=="kana"))
                continue;
            canvas.writeHeading(script_record.getScriptTag().toString());
            script = script_record.getScript();
            print_script(fs, canvas, gsub, script);
        }

        canvas.writeBitmap((filename + "_analysis.bmp").c_str());
    }
}
