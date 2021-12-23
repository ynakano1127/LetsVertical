#include "lookup.h"

Lookup::Lookup(FontSeeker& fs, uint32_t lookup_offset) : lookup_offset(lookup_offset)
{
    fs.seekFromTable(Tag('G', 'S', 'U', 'B'), lookup_offset);

    lookup_type = fs.read16();
    lookup_flag = fs.read16();
    sub_table_count = fs.read16();
    for(int i=0;i<sub_table_count;i++)
        subtable_offsets.push_back(fs.read16());
    mark_filtering_set  =fs.read16();
}
