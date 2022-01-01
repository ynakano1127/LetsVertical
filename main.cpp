#include <iostream>
#include <vector>
#include "Test/tagtest.h"
#include "Test/fontfile_test.h"
#include "Test/fontseekertest.h"
#include "Test/gsubtest.h"
#include "Test/writetest.h"
#include "Test/fontanalysis.h"
#include "Test/imagetest.h"
#include "Test/canvastest.h"

using namespace std;

int main()
{
    vector<Test*> tests;
//    tests.push_back(new FontFileTest());
//    tests.push_back(new TagTest());
//    tests.push_back(new FontSeekerTest());
//    tests.push_back(new GsubTest());
//    tests.push_back(new WriteTest());
//    tests.push_back(new FontAnalysis());
//    tests.push_back(new ImageTest());
    tests.push_back(new CanvasTest());

    for(int i=0;i<tests.size();i++){
        tests[i]->run();
    }

    return 0;
}
