#ifndef LOOKUPSUBTABLETYPE1_H
#define LOOKUPSUBTABLETYPE1_H

#include "coverage.h"

class LookupSubtableType1
{
private:
    uint32_t offset;
    uint16_t subs_format;
    Coverage coverage;
    uint16_t delta_glyph_id;
    uint16_t glyph_count;
    std::vector<uint16_t> substitute_glyph_ids;
public:
    LookupSubtableType1() = default;
    LookupSubtableType1(FontSeeker& fs, uint32_t offset);
    uint16_t convertGlyph(uint16_t glyph_id);
    uint16_t getSubsFormat() { return subs_format; }
    Coverage getCoverage() { return coverage; }
    uint16_t getDeltaGlyphId() { return delta_glyph_id; }
    std::vector<uint16_t> getSubstituteGlyphIds() { return substitute_glyph_ids; }
};

#endif // LOOKUPSUBTABLETYPE1_H
