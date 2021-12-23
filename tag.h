#ifndef TAG_H
#define TAG_H

#include <cstdint>
#include <string>

class Tag
{
private:
    uint32_t tag;
public:
    Tag() = default;
    Tag(uint32_t tag);
    Tag(char one, char two, char three, char four);
    void setTag(uint32_t tag);
    uint32_t getTag();
    std::string toString();

    bool operator<(const Tag &right) const { return this->tag < right.tag; }; // tagをmapのキーとして持つことがあるのでこれだけ定義
};

#endif // TAG_H
