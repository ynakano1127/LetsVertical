#ifndef GSUB_H
#define GSUB_H

#include "./ScriptList/scriptlist.h"
#include "./FeatureList/featurelist.h"
#include "./LookupList/lookuplist.h"

class Gsub
{
private:
    uint16_t major_version;
    uint16_t minor_version;
    ScriptList script_list;
    FeatureList feature_list;
    LookupList lookup_list;
public:
    Gsub(FontSeeker& fs);
    uint16_t getMajorVersion() { return major_version; }
    uint16_t getMinorVersion() { return minor_version; }
    ScriptList getScriptList() { return script_list; }
    FeatureList getFeatureList() { return feature_list; }
    LookupList getLookupList() { return lookup_list; }
};

#endif // GSUB_H
