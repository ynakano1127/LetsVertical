#ifndef COVERAGE_H
#define COVERAGE_H

#include <vector>

#include "rangerecord.h"

class Coverage
{
private:
    uint32_t offset;
    std::map<uint16_t, uint16_t> coverage_map;
    uint16_t coverage_format;
    uint16_t glyph_count;
    std::vector<uint16_t> glyph_array;
    uint16_t range_count;
    std::vector<RangeRecord> range_records;
public:
    Coverage() = default;
    Coverage(FontSeeker& fs, uint32_t offset);
    std::map<uint16_t, uint16_t> getCoverageMap(){ return coverage_map; };
    uint16_t getCoverageFormat() { return coverage_format; }
    std::vector<uint16_t> getGlyphArray() { return glyph_array; }
    std::vector<RangeRecord> getRangeRecords() { return range_records; }
private:
    void makeCoverageMap();
};

#endif // COVERAGE_H
