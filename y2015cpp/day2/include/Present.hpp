#ifndef __PRESENT_H__
#define __PRESENT_H__

class Present{
    // dimensions:
    int length;
    int width;
    int height;
    // areas of sides
    int side1;
    int side2;
    int side3;

    public:
        Present(int l, int w, int h);
        int wrapPaperAmount();
        int ribbonAmount();
};


#endif