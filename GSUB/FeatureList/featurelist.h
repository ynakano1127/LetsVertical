#ifndef FEATURELIST_H
#define FEATURELIST_H

#include "featurerecord.h"

class FeatureList
{
private:
    uint32_t featurelist_offset;
    uint16_t feature_count;
    std::vector<FeatureRecord> feature_list;
public:
    FeatureList() = default;
    FeatureList(FontSeeker& fs, uint32_t featurelist_offset);
    std::vector<FeatureRecord> getFeatureList() { return feature_list; }
};

#endif // FEATURELIST_H
