
#ifndef sonicTag2_imageButton_h
#define sonicTag2_imageButton_h

#include "interfaceObject.h"
#include <iostream>

using namespace std;

namespace EAVIGUI {
  
    class ImageButton : public InterfaceObject {
    public:
        ImageButton(InterfaceListener *_listener, int _id, int _x, int _y, string imageFileName);
        ImageButton(InterfaceListener *_listener, int _id, int _x, int _y, ofImage _im);
        void setColor(ofColor newCol) {imColor = newCol; invalidate();}
        ofImage getImage() {return im;}
        
        void loadNewImage(string imageFileName);

    protected:
        void init();
        virtual void drawToBuffer();
        ofImage im;
        ofColor imColor;
    };
    
};

#endif
