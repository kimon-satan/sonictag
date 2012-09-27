#include "labelButton.h"

namespace EAVIGUI {

    LabelButton::LabelButton(InterfaceListener *_listener, int _id, int _x, int _y, ofTrueTypeFont *_font, string _text, 
                             int _defaultColour, int _mouseOverColour, int _mouseDownColour, int _disabledColour)
    : InterfaceObject(_listener, _id, _x, _y) {
        font = _font;
        text = _text;
        setWidth(font->stringWidth(text));
        setHeight(font->stringHeight(text) + 1);
    //	w = font->stringWidth(text);
    //	h = font->stringHeight(text) + 1;
    //	printf("Lbl width: %d Height: %d\n", w, h);
        defaultColour = _defaultColour;
        mouseOverColour = _mouseOverColour;
        mouseDownColour = _mouseDownColour;
        disabledColour = _disabledColour;
        disabled = false;
    //	printf("Cols: %X %X %X %X\n", defaultColour, mouseOverColour, mouseDownColour, disabledColour);
    }

    void LabelButton::drawToBuffer() {
        int col=defaultColour;
        if (disabled) {
            col = disabledColour;
        }else{
            switch (mouseState) {
                case OVER:
                    col = mouseOverColour;
                    break;
                case PRESSED:
                    col = mouseDownColour;
                    break;
            }
        }
    //	cout << "State: " << mouseState << " New col: " << col << endl;
        ofSetColor(col);
        font->drawString(text, 0, h - (h/2) + 2);
    //	ofNoFill();
    //	ofRect(0,0,w,h);
    }

    void LabelButton::setText(string t) {
        text = t ;
        invalidate();
    }

    void LabelButton::setEnabled(bool val) {
        disabled = !val;
        invalidate();
    }

    void LabelButton::mouseMoved( int x, int y ) {
        InterfaceObject::mouseMoved(x,y);
        invalidate();
    }
    void LabelButton::mouseExit() {
        InterfaceObject::mouseExit();
        invalidate();	
    }

    void LabelButton::mousePressed( int x, int y, int button ) {
        InterfaceObject::mousePressed(x,y,button);
        invalidate();	
    }

    void LabelButton::mouseReleased() {
        InterfaceObject::mouseReleased();
        invalidate();		
    }

    void LabelButton::mouseReleased(int x, int y, int button ) {
        InterfaceObject::mouseReleased(x,y,button);
        sendCallback(CLICKED);
        invalidate();	
        
    }
    void LabelButton::mouseDragged(int x, int y, int button) {
        InterfaceObject::mouseDragged(x,y,button);
        invalidate();		
    }

    void LabelButton::touchDown(ofTouchEventArgs &touch) {
        mouseState = PRESSED;
        invalidate();
        InterfaceObject::touchDown(touch);
    }

    void LabelButton::touchMoved(ofTouchEventArgs &touch) {
        mouseState = PRESSED;
        invalidate();
        InterfaceObject::touchMoved(touch);
    }

    void LabelButton::touchUp(ofTouchEventArgs &touch) {
        mouseState = SOMEWHERELSE;
        invalidate();
        InterfaceObject::touchUp(touch);
    }


    void LabelButton::touchExit() {
        mouseState = SOMEWHERELSE;
        invalidate();
        InterfaceObject::touchExit();
    }
}