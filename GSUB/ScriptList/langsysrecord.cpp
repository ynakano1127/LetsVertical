#include "langsysrecord.h"

LangSysRecord::LangSysRecord(FontSeeker& fs, uint32_t script_offset) : script_offset(script_offset)
{
    lang_sys_tag.setTag(fs.read32());
    uint32_t offset = fs.read16();

    fs.savePos();
    lang_sys = LangSys(fs, script_offset + offset);
    fs.loadPos();
}
