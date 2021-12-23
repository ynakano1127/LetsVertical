#include "scriptrecord.h"

ScriptRecord::ScriptRecord(FontSeeker& fs, uint32_t scriptlist_offset) : scriptlist_offset(scriptlist_offset)
{
    script_tag.setTag(fs.read32());
    uint16_t script_offset = fs.read16();

    fs.savePos();
    script = Script(fs, scriptlist_offset + script_offset);
    fs.loadPos();
}
