#include <iostream>
#include <fstream>

#include "../GSUB/gsub.h"
#include "fontanalysis.h"

#define FONT_KIND_NUMBER 16

using namespace std;

string fonts[] = {
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

int histogram[9];

FontAnalysis::FontAnalysis()
{

}

void print_feature(ofstream& stream, Gsub& gsub, Feature& feature) {
    Lookup lookup;

    vector<Lookup> lookups = gsub.getLookupList().getLookupList();
    for(uint16_t i : feature.getLookupListIndices()){
        lookup = lookups[i];
        stream << "\t" << "\t" << "\t" << lookup.getLookupType() << endl;
        histogram[lookup.getLookupType()]++;
    }
}

void print_langsys(ofstream& stream, Gsub& gsub, LangSys& langsys) {
    Feature feature;

    vector<FeatureRecord> feature_records = gsub.getFeatureList().getFeatureList();
    for(uint16_t i : langsys.getFeatureIndices()){
        FeatureRecord r = feature_records[i];
        stream << "\t" << "\t" << r.getFeatureTag().toString() << endl;
        Feature feature = r.getFeature();
        print_feature(stream, gsub, feature);
    }
}

void print_script(ofstream& stream, Gsub& gsub, Script& script) {
    LangSys langsys;

    stream << "\t" << "DefaultLangSys" << endl;
    langsys = script.getDefaultLangSys();
    print_langsys(stream, gsub, langsys);

    for(auto lang_sys_record : script.getLangSysList()) {
        stream << "\t" << lang_sys_record.getLangSysTag().toString() << endl;
        langsys = lang_sys_record.getLangSys();
        print_langsys(stream, gsub, langsys);
    }
}

void FontAnalysis::run() {
    for(int i=0; i < 9; i++)
        histogram[i] = 0;

    for(string filename : fonts){
        ofstream stream(filename + "_analysis.txt", ios::out);

        FontSeeker fs(filename);
        Gsub gsub(fs);
        Script script;

        for(auto script_record : gsub.getScriptList().getScriptList()){
            string tag = script_record.getScriptTag().toString();
            if(!(tag=="DFLT" || tag=="hani" || tag=="kana"))
                continue;
            stream << script_record.getScriptTag().toString() << endl;
            script = script_record.getScript();
            print_script(stream, gsub, script);
        }

        stream.close();
    }

    for(int i=1; i<9; i++){
        cout << i << " " << histogram[i] << endl;
    }
}
