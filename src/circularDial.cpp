/*
 This file is part of 'Sonic Tag'.
 This software is released under a simplified BSD license, modified for non-commercial use only.
 
 Copyright (c) 2013, M.Grierson, Embodied AudioVisual Interaction Group, Goldsmiths, University of London
 
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are
 met:
 
 * Redistributions of source code must retain the above copyright
 notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above
 copyright notice, this list of conditions and the following disclaimer
 in the documentation and/or other materials provided with the
 distribution.
 * Any redistribution, use, or modification is done solely for
 personal benefit and not for any commercial purpose or for monetary
 gain
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
 For further information:
 http://eavi.goldsmithsdigital.com/sound-image-and-brain/
 http://eavi.goldsmithsdigital.com/sonic-tag/
 
 */


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