#ifndef FEATURERECORD_H
#define FEATURERECORD_H

#include "feature.h"

class FeatureRecord
{
private:
    uint32_t featurelist_offset;
    Tag feature_tag;
    Feature feature;
public:
    FeatureRecord() = default;
    FeatureRecord(FontSeeker& fs, uint32_t featurelist_offset);
    Tag getFeatureTag() { return feature_tag; }
    Feature getFeature() { return feature; }
};

#endif // FEATURERECORD_H
