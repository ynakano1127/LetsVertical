#include <iostream>
#include "imagetest.h"

#include "../image.h"

using namespace std;

ImageTest::ImageTest()
{

}

void ImageTest::run()
{
    Image image(200);
    image.clear(0x555555);
    image.fillBox(10, 10, 80, 80, 0xff0000);

    Image image2 = image;
    image2.fillBox(20, 20, 70, 70, 0x00ff00);

    Image image3;
    image3 = image2;
    image3.fillBox(30, 30, 60, 60, 0x0000ff);
//    getter
    cout << "1 " << image.getWidth() << endl;
    cout << "1 " << image.getHeight() << endl;
    cout << "2 " << image2.getWidth() << endl;
    cout << "2 " << image2.getHeight() << endl;
    cout << "3 " << image3.getWidth() << endl;
    cout << "3 " << image3.getHeight() << endl;

    for(int i=0;i<50;i++){
        image3.setPixel(i, 50-i, 0xffffff);
        image3.setPixel(i, 50+i, 0xffffff);
    }
    for(int i=50;i<100;i++){
        image3.setPixel(i, i-50, 0xffffff);
        image3.setPixel(i, 100-(i-50), 0xffffff);
    }

    for(int i=40;i<60;i++){
        for(int j=40;j<60;j++){
            image3.blendPixel(i, j, 0xff0000, 255/5);
        }
    }

    image3.drawVLine(150, 0, 100, 0xffffff);
    image3.drawHLine(0, 50, 200, 0xffffff);

    image.writeBitmap("output1.bmp");
    image2.writeBitmap("output2.bmp");
    image3.writeBitmap("output3.bmp");

    image3.expand(100, true, 0xff0000);
    image3.writeBitmap("output3-2.bmp");
    image3.expand(100, false, 0x00ff00);
    image3.writeBitmap("output3-3.bmp");
}
