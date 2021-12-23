#include "gsub.h"

Gsub::Gsub(FontSeeker& fs)
{
    fs.seekFromTable(Tag('G', 'S', 'U', 'B'), 0);

    major_version = fs.read16();
    minor_version = fs.read16();
    uint32_t scriptlist_offset = fs.read16();
    uint32_t featurelist_offset = fs.read16();
    uint32_t lookuplist_offset = fs.read16();
    script_list = ScriptList(fs, scriptlist_offset);
    feature_list = FeatureList(fs, featurelist_offset);
    lookup_list = LookupList(fs, lookuplist_offset);
}
