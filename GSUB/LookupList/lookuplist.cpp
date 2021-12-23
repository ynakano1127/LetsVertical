#include "lookuplist.h"

LookupList::LookupList(FontSeeker& fs, uint32_t lookuplist_offset) : lookuplist_offset(lookuplist_offset)
{
    fs.seekFromTable(Tag('G', 'S', 'U', 'B'), lookuplist_offset);

    lookup_count = fs.read16();
    for(int i=0;i<lookup_count;i++){
        uint16_t lookup_offset = fs.read16();

        fs.savePos();
        Lookup l(fs, lookuplist_offset + lookup_offset);
        lookup_list.push_back(l);
        fs.loadPos();
    }
}
