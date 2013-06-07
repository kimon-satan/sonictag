#include "label.h"

namespace EAVIGUI {

    Label::Label(InterfaceListener *_listener, int _id, int _x, int _y, int _w, int _h, ofTrueTypeFont *_font, string _text, ofColor _color) : InterfaceObject(_listener, _id, _x, _y) {
        font = _font;
        text = _text;
        colour = _color;
        setWidth(_w);
        setHeight(_h);
        setIsInteractive(false);
        backgroundColour = ofColor(0,0,0,0);
    }
    
    void Label::fitToText() {
        setWidth(font->stringWidth(text));
        setHeight(font->getLineHeight() * 1.3);
    }

    void Label::drawToBuffer() {
        ofFill();
        ofSetColor(backgroundColour);
        ofRect(0,0, w, h);
        ofSetColor(colour);
        font->drawString(text, 0, font->getLineHeight());
        
    }

    void Label::setText(string t) {
        text = t ;
        invalidate();
    }

    
}
