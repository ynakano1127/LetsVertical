#include <iostream>
#include "canvastest.h"

#include "../canvas.h"

using namespace std;

CanvasTest::CanvasTest()
{

}

void CanvasTest::run()
{
    Canvas c("NotoSerifJP-Regular.otf", 1000, 1000, 10, 50, 16, 120);
    /*
    c.loadGlyph(0x2022);
    c.writeGlyph(30, 30);
    c.writeString("hello", 30, 30);
    c.drawHLine(0, 30, 60, 0x000000);
    c.drawVLine(30, 0, 60, 0x000000);
    */
    c.writeHeading("DFLT");
    c.writeHeading("JAN ", 1);
    c.writeHeading("vert ", 2);
    c.writeHeading("1 ", 3);
    for(int i=0; i<30; i++)
        c.writeGlyphPair(0x2022, 0x2022);

    c.writeHeading("DFLT");
    c.writeHeading("JAN ", 1);
    c.writeHeading("vert ", 2);
    c.writeHeading("1 ", 3);
    for(int i=0; i<30; i++)
        c.writeGlyphPair(0x2022, 0x2022);
    c.writeBitmap("output.bmp");
}
