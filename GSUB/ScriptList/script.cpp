#include "script.h"

Script::Script(FontSeeker& fs, uint32_t script_offset) : script_ofset(script_offset)
{
    fs.seekFromTable(Tag('G', 'S', 'U', 'B'), script_offset);

    uint16_t default_offset = fs.read16();
    if(default_offset != 0){
        fs.savePos();
        default_lang_sys = LangSys(fs, script_offset + default_offset);
        fs.loadPos();
    }

    lang_sys_count = fs.read16();
    for(int i=0;i<lang_sys_count;i++){
        LangSysRecord ls(fs, script_offset);
        lang_sys_list.push_back(ls);
    }
}
