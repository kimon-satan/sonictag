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
#include "RadialScratchSurface.h"
#include "geomFunctions.h"

namespace EAVIGUI {
    
    RadialScratchSurface::RadialScratchSurface(InterfaceListener *_listener, int _id, int _x, int _y, int _w, int _h) : InterfaceObject(_listener, _id, _x, _y){
        setWidth(_w);
        setHeight(_h);
        showAngle = false;
        touchX =  midX = w/2.0;
        touchY = midY = h/2.0;
        velocity = 0.0;
        setDeviceScaling(false);
        
        fboD = 512;
        ofFbo::Settings settings;
        settings.width			= fboD;
        settings.height			= fboD;
        fboWidth = settings.width;
        fboHeight = settings.height;
        settings.useDepth		= false;
        settings.useStencil		= false;
        fbo1.allocate(settings);
        fbo2.allocate(settings);
        velocity=0;
        distToCenter = 100;
        angle = PI;
        
    }
        
    void RadialScratchSurface::drawToBuffer() {
        fbo1.begin();
        ofSetColor(255,255,255,230);
        float blur = sin(ofGetFrameNum() * 0.002) * 0.02 * fboD;
        float blur2 = sin(ofGetFrameNum() * 0.001) * 0.01 * fboD;
        fbo2.draw(-blur2,-blur2 + blur, fboD + blur + blur2, fboD + blur);
        ofNoFill();
        ofSetLineWidth(2.0);
        ofSetColor(0,250,0,240);
        if (showAngle) {
            float ptx = touchX / (float) w * fboD;
            float pty = touchY / (float) h * fboD;
            ofLine(ptx, pty, fboD/2, fboD/2);
            ofCircle(ptx, pty, 50);
            ofFill();
            ofSetColor(0,230,0,140);
            ofCircle(ptx, pty, 50);
        }
        fbo1.end();
        
        fbo2.begin();
        ofSetColor(255,255,255,255);
        fbo1.draw(0,0, fboD, fboD);
        fbo2.end();
        
        fbo1.draw(0,0,w,h);
        invalidate();
    }
    

    
    void RadialScratchSurface::touchDown(ofTouchEventArgs &touch) {
        InterfaceObject::touchDown(touch);
        processTouch(touch);
    }
    
    void RadialScratchSurface::touchMoved(ofTouchEventArgs &touch) {
        InterfaceObject::touchMoved(touch);
        processTouch(touch);
    }
    
    void RadialScratchSurface::touchUp(ofTouchEventArgs &touch) {
        InterfaceObject::touchUp(touch);
        showAngle = false;
        invalidate();
        sendCallback(InterfaceObject::TOUCHUP);
    }
    
    void RadialScratchSurface::processTouch(ofTouchEventArgs &touch) {
        if (0 == touch.id)
        {
            showAngle = true;
            //get angle between now and last point, if mid point is center of triangle
            //using law of cosines http://oakroadsystems.com/twt/solving.htm#eq30
            float distA = geom::distBetween(touch.x, touch.y, touchX, touchY);
            float distB = geom::distBetween(touch.x, touch.y, midX, midY);
            float distC = geom::distBetween(touchX, touchY, midX, midY);
            float cosA  =0;
            if (distB > 0 && distC > 0) {
                cosA = ((distB * distB) + (distC * distC) - (distA * distA)) / (2.0 * distB * distC);
            }
            velocity = acos(cosA);
            touchX = touch.x;
            touchY = touch.y;
            distToCenter = distB;
            angle = geom::angleBetween(touch.x, touch.y, w/2.0, h/2.0) + PI;
            invalidate();
            sendCallback(InterfaceObject::TOUCHMOVED);
        }
    }
    
    
    
}