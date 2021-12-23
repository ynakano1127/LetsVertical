#ifndef LOOKUPLIST_H
#define LOOKUPLIST_H
#include <cstdint>
#include <vector>
#include "lookup.h"
#include "../../fontseeker.h"


class LookupList
{
private:
    uint32_t lookuplist_offset;
    uint16_t lookup_count;
    std::vector<Lookup> lookup_list;
public:
    LookupList() = default;
    LookupList(FontSeeker& fs, uint32_t lookuplist_offset);
    std::vector<Lookup> getLookupList() { return lookup_list; }
};

#endif // LOOKUPLIST_H
