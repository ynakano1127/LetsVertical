#include <iostream>
#include "tagtest.h"
#include "../tag.h"

using namespace std;

TagTest::TagTest()
{

}

void TagTest::run(){
    Tag tag(0x41424344);
    cout << tag.getTag() <<endl;
    cout << tag.toString() <<endl;
    tag.setTag(0x7a797877);
    cout << tag.getTag() <<endl;
    cout << tag.toString() << endl;
    Tag tag2('G','P','O','S');
    cout << tag2.getTag() <<endl;
    cout << tag2.toString() << endl;
}
