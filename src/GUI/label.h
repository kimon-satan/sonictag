
#ifndef _LABEL_H
#define _LABEL_H

#include "interfaceObject.h"
#include <iostream>
//#include "ofmain.h"

using namespace std;

namespace EAVIGUI {

    class Label : public InterfaceObject {
    public:
        Label(InterfaceListener *_listener, int _id, int _x, int _y, int _w, int _h, ofTrueTypeFont *_font, string _text, ofColor _colour);
        void setText(string t);
        ofTrueTypeFont *font;
        ofColor colour, backgroundColour;
        void fitToText();
    protected:
        void drawToBuffer();
        string text;
        
    };

}
#endif

