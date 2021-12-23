#include "featurelist.h"

FeatureList::FeatureList(FontSeeker& fs, uint32_t featurelist_offset) : featurelist_offset(featurelist_offset)
{
    fs.seekFromTable(Tag('G', 'S', 'U', 'B'), featurelist_offset);

    feature_count = fs.read16();
    for(int i=0;i<feature_count;i++){
        FeatureRecord r(fs, featurelist_offset);
        feature_list.push_back(r);
    }
}
