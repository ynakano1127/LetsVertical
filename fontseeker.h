#ifndef FONTSEEKER_H
#define FONTSEEKER_H

#include <map>
#include <stack>

#include "fontfile.h"
#include "tag.h"

class FontSeeker
{
private:
    FontFile font_file;
    std::stack<uint32_t> pos_save;
    std::map<Tag, uint32_t> table_offsets;
public:
    FontSeeker(std::string font_file_name);
    ~FontSeeker();
    void savePos();
    void loadPos();
    void gotoTable(Tag tag);
    uint8_t read8();
    uint16_t read16();
    uint32_t read32();
    void seek(uint32_t pos);
    void seekFromNowPos(uint32_t pos);
    void seekFromTable(Tag tag, uint32_t pos);
};

#endif // FONTSEEKER_H
