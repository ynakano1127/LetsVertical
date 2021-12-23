#ifndef SCRIPTLIST_H
#define SCRIPTLIST_H

#include "scriptrecord.h"

class ScriptList
{
private:
    uint32_t scriptlist_offset;
    uint16_t script_count;
    std::vector<ScriptRecord> script_list;
public:
    ScriptList() = default;
    ScriptList(FontSeeker& fs, uint32_t scriptlist_offset);
    std::vector<ScriptRecord> getScriptList() { return script_list; }
};

#endif // SCRIPTLIST_H
