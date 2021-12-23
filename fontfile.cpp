#include "fontfile.h"

using namespace std;

FontFile::FontFile(string filename) : filename(filename)
{

}

FontFile::~FontFile(){
    if(isOpen()){
        close();
    }
}

bool FontFile::isOpen(){
    return stm.is_open();
}

void FontFile::open(){
    stm.open(filename);
}

void FontFile::close(){
    stm.close();
}

void FontFile::seekCur(uint32_t seek){
    stm.seekg(seek, ios_base::cur);
}

void FontFile::seekBeg(uint32_t seek){
    stm.seekg(seek, ios_base::beg);
}

void FontFile::read(char* buff, uint32_t n){
    stm.read(buff, n);
}

uint32_t FontFile::position(){
    return stm.tellg();
}
