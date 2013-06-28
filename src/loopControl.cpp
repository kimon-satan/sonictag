//
//  loopControl.cpp
//  SonicTag3
//
//  Created by Chris on 28/06/2013.
//
//

#include "loopControl.h"
#include "EAVIGUI.geomFunctions.h"

namespace EAVIGUI {
    LoopControl::LoopControl(InterfaceListener *_listener, int _id, int _x, int _y, int w, int h, sharedDataContainer *_data) :
    InterfaceObject(_listener, _id, _x, _y), data(_data) {
        setWidth(w);
        setHeight(h);
        caretPos.x = 30;
        caretPos.y = 30;
        setIsInteractive(true);
        start = 0;
        end = 1;
    }
    
    void LoopControl::drawToBuffer() {
        ofSetColor(0,255,0);
        ofNoFill();
        ofCircle(w/2, h/2, w/4);
        ofCircle(w/2, h/2, w/3);
        ofSetColor(ofColor::gray);
        ofCircle(caretPos.x, caretPos.y, 30);
        ofLine(caretPos.x, caretPos.y, cx, cy);
        ofVec2f endPt;
        endPt.x = 200;
        endPt.y = 0;
        endPt = endPt.rotateRad(end * TWO_PI);
        ofSetColor(100,0,0,255);
        ofLine(cx, cy, cx + endPt.x, cy + endPt.y);
        cout << endPt << endl;
    }

    void LoopControl::touchDown(ofTouchEventArgs &touch) {
        InterfaceObject::touchDown(touch);
        moveCaret(touch);
    }
    
    void LoopControl::touchMoved(ofTouchEventArgs &touch) {
        InterfaceObject::touchMoved(touch);
        moveCaret(touch);
    }
    
    void LoopControl::touchUp(ofTouchEventArgs &touch) {
        InterfaceObject::touchUp(touch);
        
    }
    
    void LoopControl::moveCaret(ofTouchEventArgs &touch) {
        caretPos.x = touch.x;
        caretPos.y = touch.y;
//        cout << geom::angleBetween(caretPos.x, caretPos.y, cx, cy) << ", " << geom::distBetween(caretPos.x, caretPos.y, cx, cy) << endl;
        float angle = geom::angleBetween(caretPos.x, caretPos.y, cx, cy);
        if (angle < 0) angle += TWO_PI;
        float sampleStart = angle / TWO_PI;
        start = sampleStart;
        end = sampleStart + min((geom::distBetween(caretPos.x, caretPos.y, cx, cy) / (w/2.0)), 1.0 - sampleStart);
        cout << sampleStart << " : " << end << endl;
        invalidate();
    }


};
