//
//  sceneFingerPlayPitch.cpp
//  sonicTag2
//
//  Created by Chris Kiefer on 05/07/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#include <iostream>
#include "sceneFingerPlayPitch.h"

void sceneFingerPlayPitch::setup(sharedDataContainer *data) {
    sceneFingerPlay::setup(data);
    angularVelocity = 0.0;
    lastAngle = 0;
    velMA.resize(10);
}

float sceneFingerPlayPitch::getNextSample() {
    return sharedData->buffer.play(velMA.value());    
}

void sceneFingerPlayPitch::update() {
    if (lastAngle != angle) {
        if (lastAngle > PI && angle < PI) {
            angularVelocity = (TWOPI-lastAngle) + angle;
        }else if (angle > PI && lastAngle < PI) {
            angularVelocity = (TWOPI - angle) + lastAngle;
        }else{
            fabs(angle - lastAngle);
        }
        angularVelocity = fabs(angle - lastAngle);
        lastAngle = angle;
        isPlaying = true;
        onCounter=10;
        velMA.addSample(angularVelocity * 2);
        cout << velMA.value() << endl;
    }else {
        onCounter--;
        if (onCounter <= 0)
            isPlaying = false;
    }    
}

void sceneFingerPlayPitch::touchMoved(ofTouchEventArgs &touch) {
    if (0 == touch.id) {
        px = touch.x;
        py = touch.y;
//        cout << ofDist(px, py, ofGetWidth()/2.0, ofGetHeight()/2.0) << ", ";
//        cout << angleBetween(px, py, ofGetWidth()/2.0, ofGetHeight()/2.0) << endl;
        angle = geom::angleBetween(px, py, ofGetWidth()/2.0, ofGetHeight()/2.0) + PI;
        log::write(log::ANGLE, angle);
    }    
}
