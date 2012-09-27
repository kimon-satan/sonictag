//
//  circularDial.cpp
//  DRSApp
//
//  Created by Chris Kiefer on 31/07/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#include <iostream>
#include "circularDial.h"
#include "geomFunctions.h"

namespace EAVIGUI {

    CircularDial::CircularDial(InterfaceListener *_listener, int _id, int _x, int _y, int _w, int _h) : InterfaceObject(_listener, _id, _x, _y){
        setWidth(_w);
        setHeight(_h);
        divisions = 120;
        pulsate = true;
        pulsateMin = 0.3;
        pulsateSpeed = 0.002;
    }

    void CircularDial::setValue(float newValue) {
        value = newValue;
        invalidate();
    }
   
    void CircularDial::drawToBuffer() {
        ofFill();
        ofEnableSmoothing();
        ofEnableAlphaBlending();
        ofSetLineWidth(1);
        float hw = (w/2.0);
        float hh = (h/2.0);
        ofBeginShape();
        ofSetColor(223,0,255,255);
        float cr = min(hw,hh) * 0.95;
        float angle = 0;
        while (angle < (TWO_PI * value) ) {
            ofCurveVertex(hw + (cr*cos(angle + PI)), hh+(cr * sin(angle + PI)));
            angle += TWO_PI / divisions;
        }
        cr *= 0.8;
        while (angle > TWO_PI / divisions ) {
            angle -= TWO_PI / divisions;
            ofCurveVertex(hw + (cr*cos(angle + PI)), hh+(cr * sin(angle + PI)));
        }
        ofEndShape();
        
        //draw the border
        ofBeginShape();
        ofNoFill();
        ofSetColor(200,200,200);
        cr = min(hw,hh) * 0.95;
        angle = 0;
        while (angle < (TWO_PI * 1.0) ) {
            ofCurveVertex(hw + (cr*cos(angle + PI)), hh+(cr * sin(angle + PI)));
            angle += TWO_PI / divisions;
        }
        cr *= 0.8;
        while (angle > TWO_PI / divisions ) {
            angle -= TWO_PI / divisions;
            ofCurveVertex(hw + (cr*cos(angle + PI)), hh+(cr * sin(angle + PI)));
        }
        ofEndShape();
    }
    
    void CircularDial::touchDown(ofTouchEventArgs &touch) {
        processTouch(touch);
    }

    void CircularDial::touchMoved(ofTouchEventArgs &touch) {
        processTouch(touch);
    }
    
    void CircularDial::processTouch(ofTouchEventArgs &touch) {
        if (0 == touch.id) {
            float angle = geom::angleBetween(touch.x, touch.y, getScaledWidth()/2.0, getScaledHeight()/2.0) + PI;
            setValue(angle/TWO_PI);
        }        
        sendCallback(InterfaceObject::TOUCHMOVED);
    }



}