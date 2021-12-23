#ifndef LOOKUP_H
#define LOOKUP_H

#include <vector>

#include "../../fontseeker.h"

class Lookup
{
private:
    uint32_t lookup_offset;
    uint16_t lookup_type;
    uint16_t lookup_flag;
    uint16_t sub_table_count;
    std::vector<uint16_t> subtable_offsets;
    uint16_t mark_filtering_set;
public:
    Lookup() = default;
    Lookup(FontSeeker& fs, uint32_t lookup_offset);
    uint32_t getLookupOffset() { return lookup_offset; }
    uint16_t getLookupType() { return lookup_type; }
    uint16_t getLookupFlag() { return lookup_flag; }
    std::vector<uint16_t> getSubtableOffsets() { return subtable_offsets; }
    uint16_t getMarkFilteringSet() { return mark_filtering_set; }
};

#endif // LOOKUP_H
