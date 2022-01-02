#include <iostream>

#include "gsubtest.h"
#include "../GSUB/gsub.h"
#include "../GSUB/LookupList/lookupsubtabletype1.h"

using namespace std;

GsubTest::GsubTest()
{

}

void GsubTest::run(){
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
//                cout << l.getLookupOffset() + offset << endl;
    }

    Coverage coverage = lst1_list[0].getCoverage();
    for(const auto &item: coverage.getCoverageMap()){
        std::cout << std::dec << item.first << " -> " << lst1_list[0].convertGlyph(item.first) << std::endl;
    }
}
