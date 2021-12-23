#include "tag.h"

using namespace std;

Tag::Tag(uint32_t tag) : tag(tag)
{

}

Tag::Tag(char one, char two, char three, char four){
    tag = (uint8_t)one << 24 |
        (uint8_t)two << 16 |
        (uint8_t)three << 8 |
        (uint8_t)four << 0;
}

void Tag::setTag(uint32_t tag){
    this->tag = tag;
}

uint32_t Tag::getTag(){
    return tag;
}

std::string Tag::toString(){
    string buff;
    buff += tag >> 24;
    buff += (tag >> 16) & 255;
    buff += (tag >> 8) & 255;
    buff += tag & 255;
    return buff;
}
