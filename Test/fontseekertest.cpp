#include <iostream>
#include "fontseekertest.h"
#include "../fontseeker.h"

using namespace std;

FontSeekerTest::FontSeekerTest()
{

}

void FontSeekerTest::run(){
    FontSeeker seeker("NotoSansCJKjp-Thin.otf");
    seeker.savePos();

    cout << Tag(seeker.read32()).toString() <<endl;
    cout << seeker.read16() <<endl;

    seeker.loadPos();
    cout << Tag(seeker.read32()).toString() <<endl;
    cout << seeker.read16() <<endl;

    seeker.gotoTable(Tag(0x47535542));
    cout << seeker.read16() << endl;
    cout << seeker.read16() << endl;
    cout << seeker.read16() << endl;
    cout << seeker.read16() << endl;
    cout << seeker.read16() << endl;

    seeker.seek(0);
    cout << Tag(seeker.read32()).toString() <<endl;
    cout << seeker.read16() <<endl;


    seeker.seekFromTable(Tag(0x47535542), 4);
    cout << seeker.read16() <<endl;
    cout << seeker.read16() <<endl;


}
