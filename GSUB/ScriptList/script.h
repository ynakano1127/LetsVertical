#ifndef SCRIPT_H
#define SCRIPT_H

#include "langsysrecord.h"

class Script
{
private:
    uint32_t script_ofset;
    LangSys default_lang_sys;
    uint16_t lang_sys_count;
    std::vector<LangSysRecord> lang_sys_list;
public:
    Script() = default;
    Script(FontSeeker& fs, uint32_t script_offset);
    LangSys getDefaultLangSys(){ return default_lang_sys; }
    std::vector<LangSysRecord> getLangSysList() { return lang_sys_list; }
};

#endif // SCRIPT_H
