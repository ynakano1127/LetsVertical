#ifndef SCRIPTRECORD_H
#define SCRIPTRECORD_H

#include "script.h"

class ScriptRecord
{
private:
    uint32_t scriptlist_offset;
    Tag script_tag;
    Script script;
public:
    ScriptRecord() = default;
    ScriptRecord(FontSeeker& fs, uint32_t scriptlist_offset);
    Tag getScriptTag(){ return script_tag; }
    Script getScript(){ return script; }
};

#endif // SCRIPTRECORD_H
