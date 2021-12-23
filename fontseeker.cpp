#include "fontseeker.h"
#include <iostream>

using namespace std;

FontSeeker::FontSeeker(string font_file_name) : font_file(font_file_name)
{
    font_file.open();
    if(!font_file.isOpen())
        return;

    seekFromNowPos(4);
    uint16_t table_count = read16();
    seekFromNowPos(2*3);
    for(int i=0;i<table_count;i++){
        Tag tag = Tag(read32());
        read32();
        uint32_t offset = read32();
        read32();
//        cout << tag.toString() << " " << hex << offset<< endl;
        table_offsets.insert(make_pair(tag, offset));
    }

    seek(0);
}

FontSeeker::~FontSeeker(){
    if(font_file.isOpen())
        font_file.close();
}

void FontSeeker::savePos(){
    pos_save.push(font_file.position());
}

void FontSeeker::loadPos(){
    seek(pos_save.top());
    pos_save.pop();
}

void FontSeeker::gotoTable(Tag tag){
    seek(table_offsets[tag]);
}

uint8_t FontSeeker::read8(){
    uint8_t buff[1];
    font_file.read((char*)buff, 1);
    return (uint8_t)buff[0];
}

uint16_t FontSeeker::read16(){
    uint8_t buff[2];
    font_file.read((char*)buff, 2);
    return (uint16_t)((uint16_t)buff[0] << 8) + buff[1];
}

uint32_t FontSeeker::read32(){
    uint8_t b[4];
    font_file.read((char*)b, 4);
    return ((uint32_t)b[0] << 24) | ((uint32_t)b[1] << 16) | ((uint32_t)b[2] << 8) | b[3];;
}

void FontSeeker::seek(uint32_t pos){
    font_file.seekBeg(pos);
}

void FontSeeker::seekFromNowPos(uint32_t pos){
    font_file.seekCur(pos);
}

void FontSeeker::seekFromTable(Tag tag, uint32_t pos){
    gotoTable(tag);
    seekFromNowPos(pos);
}
