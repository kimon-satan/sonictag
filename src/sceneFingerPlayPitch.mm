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
