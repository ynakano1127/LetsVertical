#include "coverage.h"

Coverage::Coverage(FontSeeker& fs, uint32_t offset) : offset(offset)
{
    fs.seekFromTable(Tag('G', 'S', 'U', 'B'), offset);

    coverage_format = fs.read16();
    if(coverage_format == 1){
        glyph_count = fs.read16();
        for(int i=0;i<glyph_count;i++){
            glyph_array.push_back(fs.read16());
        }
    }else if(coverage_format == 2){
        range_count = fs.read16();
        for(int i=0;i<range_count;i++){
            RangeRecord r(fs);
            range_records.push_back(r);
        }
    }

    makeCoverageMap();
}

void Coverage::makeCoverageMap() {
    if(coverage_format == 1){
        for(int i=0; i<glyph_array.size() ;i++){
            coverage_map.insert(std::make_pair(glyph_array[i], i));
        }
    }else if(coverage_format == 2){
        for(int i=0; i<range_count; i++){
            RangeRecord r = range_records[i];
            for(int j=r.getStartGlyphId(); j<=r.getEndGlyphId(); j++){
                uint16_t c_index = j - r.getStartGlyphId() + r.getStartCoverageIndex();
                coverage_map.insert(std::make_pair(j, c_index));
            }
        }
    }
}
