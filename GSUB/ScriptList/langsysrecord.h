#ifndef LANGSYSRECORD_H
#define LANGSYSRECORD_H

#include "langsys.h"

class LangSysRecord
{
private:
    uint32_t script_offset;
    Tag lang_sys_tag;
    LangSys lang_sys;
public:
    LangSysRecord() = default;
    LangSysRecord(FontSeeker& fs, uint32_t script_offset);
    Tag getLangSysTag(){ return lang_sys_tag; }
    LangSys getLangSys() { return lang_sys; }
};

#endif // LANGSYSRECORD_H
