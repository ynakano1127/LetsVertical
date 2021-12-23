#include "langsys.h"

LangSys::LangSys(FontSeeker& fs, uint32_t langsys_offset) : langsys_offset(langsys_offset)
{
    fs.seekFromTable(Tag('G', 'S', 'U', 'B'), langsys_offset);

    lookup_order = fs.read16();
    required_feature_index = fs.read16();
    feature_index_count = fs.read16();
    for(int i=0;i<feature_index_count;i++)
        feature_indices.push_back(fs.read16());
}
