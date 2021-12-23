#ifndef LANGSYS_H
#define LANGSYS_H

#include <vector>

#include "../../fontseeker.h"

class LangSys
{
private:
    uint32_t langsys_offset;
    uint16_t lookup_order;
    uint16_t required_feature_index;
    uint16_t feature_index_count;
    std::vector<uint16_t> feature_indices;
public:
    LangSys() = default;
    LangSys(FontSeeker& fs, uint32_t langsys_offset);
    uint16_t getLookupOrder() { return lookup_order; }
    uint16_t getRequiredFeatureIndex() { return required_feature_index; }
    std::vector<uint16_t> getFeatureIndices() { return feature_indices; }
};

#endif // LANGSYS_H
