#ifndef FONTFILE_H
#define FONTFILE_H
#include <fstream>
#include <string>

class FontFile
{
private:
    std::ifstream stm;
    std::string filename;

public:
    FontFile(std::string filename);
    ~FontFile();
    bool isOpen();
    void open();
    void close();
    void seekBeg(uint32_t seek);
    void seekCur(uint32_t seek);
    void read(char* buff, uint32_t n);
    uint32_t position();

    FontFile(const FontFile& fontfile) = delete;
    FontFile& operator=(const FontFile& fontfile) = delete;
};

#endif // FONTFILE_H
