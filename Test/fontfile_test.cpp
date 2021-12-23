#include <iostream>

#include "fontfile_test.h"
#include "../fontfile.h"

using namespace std;

FontFileTest::FontFileTest()
{

}

void FontFileTest::run(){
    FontFile file("NotoSansCJKjp-Thin.otf");
    char buff[10];
    for(int i=0;i<10;i++)
        buff[i] = '\0';

    cout<<file.isOpen()<<endl;
    file.open();
    cout<<file.isOpen()<<endl;

    file.read(buff, 4);
    cout<<buff<<endl;
    cout<< file.position() <<endl;

    file.read(buff, 2);
    cout<< (int32_t)(buff[0] << 8) + buff[1] <<endl;
    cout<< file.position() <<endl;

    file.seekBeg(0);
    file.read(buff, 4);
    cout<<buff<<endl;
    cout<< file.position() <<endl;

    file.seekBeg(0);
    file.seekBeg(4);
    file.read(buff, 2);
    cout<< (int32_t)(buff[0] << 8) + buff[1] <<endl;
    cout<< file.position() <<endl;

    cout<<file.isOpen()<<endl;
    file.close();
    cout<<file.isOpen()<<endl;
}
