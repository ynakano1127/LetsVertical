#ifndef RANGERECORD_H
#define RANGERECORD_H

#include <vector>

#include "../../fontseeker.h"

class RangeRecord
{
private:
    uint16_t start_glyph_id;
    uint16_t end_glyph_id;
    uint16_t start_coverage_index;
public:
    RangeRecord() = default;
    RangeRecord(FontSeeker& fs);
    uint16_t getStartGlyphId() { return start_glyph_id; };
    uint16_t getEndGlyphId() { return end_glyph_id; };
    uint16_t getStartCoverageIndex() { return start_coverage_index; };
};

#endif // RANGERECORD_H
