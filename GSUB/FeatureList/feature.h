#ifndef FEATURE_H
#define FEATURE_H

#include <vector>

#include "../../fontseeker.h"

class Feature
{
private:
    uint32_t feature_offset;
    uint16_t feature_params;
    uint16_t lookup_index_count;
    std::vector<uint16_t> lookup_list_indices;
public:
    Feature() = default;
    Feature(FontSeeker& fs, uint32_t feature_offset);
    uint16_t getFeatureParams() { return feature_params; }
    std::vector<uint16_t> getLookupListIndices() { return lookup_list_indices; }
};

#endif // FEATURE_H
