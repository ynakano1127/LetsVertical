#include "feature.h"

Feature::Feature(FontSeeker& fs, uint32_t feature_offset) : feature_offset(feature_offset)
{
    fs.seekFromTable(Tag('G', 'S', 'U', 'B'), feature_offset);

    feature_params = fs.read16();
    lookup_index_count  =fs.read16();
    for(int i=0;i<lookup_index_count;i++)
        lookup_list_indices.push_back(fs.read16());
}
