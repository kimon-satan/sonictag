//
//  RadialScratchSurface.cpp
//  DRSApp
//
//  Created by Chris Kiefer on 01/08/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

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
        
    }
        
    void RadialScratchSurface::drawToBuffer() {
        fbo1.begin();
        ofSetColor(255,255,255,230);
        float blur = sin(ofGetFrameNum() * 0.002) * 0.02 * fboD;
        float blur2 = sin(ofGetFrameNum() * 0.001) * 0.01 * fboD;
        fbo2.draw(-blur2,-blur2 + blur, fboD + blur + blur2, fboD + blur);
//        ofFill();
//        ofSetColor(100, 100, 100, 100);
//        ofRect(0, 0, w, h);
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
//        if (ofRandomuf() < 0.1) {
//            ofFill();
//            ofSetColor(ofRandom(255),ofRandom(255),ofRandom(255),ofRandom(255));
//            ofCircle(ofRandom(fboD), ofRandom(fboD), ofRandom(50));
//        }
        fbo1.end();
        
        fbo2.begin();
        ofSetColor(255,255,255,255);
        fbo1.draw(0,0, fboD, fboD);
        fbo2.end();
        
        fbo1.draw(0,0,w,h);
        invalidate();
    }
    

    
    void RadialScratchSurface::touchDown(ofTouchEventArgs &touch) {
        processTouch(touch);
    }
    
    void RadialScratchSurface::touchMoved(ofTouchEventArgs &touch) {
        processTouch(touch);
    }
    
    void RadialScratchSurface::touchUp(ofTouchEventArgs &touch) {
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
        }
        invalidate();
        sendCallback(InterfaceObject::TOUCHMOVED);
    }
    
    
    
}