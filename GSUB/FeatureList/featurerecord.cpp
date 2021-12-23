#include "featurerecord.h"

FeatureRecord::FeatureRecord(FontSeeker& fs, uint32_t featurelist_offset) : featurelist_offset(featurelist_offset)
{
    feature_tag = Tag(fs.read32());
    uint16_t feature_offset = fs.read16();

    fs.savePos();
    feature = Feature(fs, featurelist_offset + feature_offset);
    fs.loadPos();
}
