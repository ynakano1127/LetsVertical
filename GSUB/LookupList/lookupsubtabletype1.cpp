#include "lookupsubtabletype1.h"
#include <iostream>

LookupSubtableType1::LookupSubtableType1(FontSeeker& fs, uint32_t offset) : offset(offset)
{
    fs.seekFromTable(Tag('G', 'S', 'U', 'B'), offset);

    subs_format = fs.read16();
    uint16_t coverage_offest = fs.read16();

    fs.savePos();
    coverage = Coverage(fs, offset + coverage_offest);
    fs.loadPos();

    if(subs_format == 1){
        delta_glyph_id = fs.read16();
    }else if(subs_format == 2){
        glyph_count = fs.read16();
        for(int i=0;i<glyph_count;i++)
            substitute_glyph_ids.push_back(fs.read16());
    }else{
        // ????
    }
}

uint16_t LookupSubtableType1::convertGlyph(uint16_t glyph_id) {
    std::map<uint16_t, uint16_t> map = coverage.getCoverageMap();
    if(map.find(glyph_id) == map.end()){ // map doesn't contain
        return glyph_id;
    }

    uint16_t c_index = map[glyph_id];
    if(subs_format == 1){
        return glyph_id + delta_glyph_id;
    }else if(subs_format == 2){
        return substitute_glyph_ids[c_index];
    }else{
         // ????
        return 0;
    }
}
