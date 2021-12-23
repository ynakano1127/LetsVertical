#include "scriptlist.h"

ScriptList::ScriptList(FontSeeker& fs, uint32_t scriptlist_offset) : scriptlist_offset(scriptlist_offset)
{
    fs.seekFromTable(Tag('G', 'S', 'U', 'B'), scriptlist_offset);

    script_count = fs.read16();
    for(int i=0;i<script_count;i++){
        ScriptRecord r(fs, scriptlist_offset);
        script_list.push_back(r);
    }
}
