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
#include "sceneAccelStretch.h"

void sceneAccelStretch::setup(sharedDataContainer *data) {
    sceneFingerStretch::setup(data);
    lastX = lastY = lastZ = 0;
    accelTotalMA = EAIT::MovingAverageF(20);
    ampMA = EAIT::MovingAverageF(20);
    pitchMA = EAIT::MovingAverageF(50);
    setThreshold(THRESHLOW);
    motionTrig = EAIT::BasicTriggerF(motionThresh, 0.005, 30);
    motionTriggering = false;
    
    sensitivity = 0.5;
}

void sceneAccelStretch::draw() {
}

void sceneAccelStretch::setThreshold(thresholdtypes t) {
    switch(t) {
        case THRESHLOW:
            motionThresh = 0.08;;
            break;
        case THRESHHIGH:
            motionThresh = 0.3;
            break;
    }
    motionTrig.onThreshold = motionThresh;
    motionTrig.offThreshold = motionThresh * 0.9;
    motionTrig.reset();
    threshType = t;
    updateTitle();
}


void sceneAccelStretch::update() {
    float diffX = fabs(ofxAccelerometer.getForce().x - lastX);
    float diffY = fabs(ofxAccelerometer.getForce().y - lastY);
    float diffZ = fabs(ofxAccelerometer.getForce().z - lastZ);
    float totalAccel = diffX + diffY + diffZ;
    accelTotalMA.addSample(totalAccel);
    bool trig = motionTrig.newFrame(accelTotalMA.value());
    ampMA.addSample(trig);
    cout << accelTotalMA.value() << ", " << trig << ", " << ampMA.value() << endl;
    lastX = ofxAccelerometer.getForce().x;
    lastY = ofxAccelerometer.getForce().y;
    lastZ = ofxAccelerometer.getForce().z;
    
    log::write(log::ACCEL, lastX, lastY, lastZ);
    rateVal = (ofxAccelerometer.getForce().x * 1.0);
    float sign = 1.0;
    if (rateVal < 0.0) sign = -1.0;
    rateVal = pow(fabs(rateVal), sensitivity);
    rateVal *= sign;
    rateVal += 1.0;

    pitchVal = (ofxAccelerometer.getForce().y * 1.0);
    sign = 1.0;
    if (pitchVal < 0.0) sign = -1.0;
    pitchVal = pow(fabs(pitchVal), sensitivity);
    pitchVal *= sign;
    pitchVal += 1.0;
    pitchMA.addSample(pitchVal);
}

float sceneAccelStretch::getNextSample() {
    float x = pitchStretch->play(1, rateVal, 0.05, 2, 0.0);
    if (motionTriggering) {
        x *= ampMA.value();
    }
    return x;
}

void sceneAccelStretch::touchDown(ofTouchEventArgs &touch) {
//    motionThresh = maxiMap::linlin(touch.y, 0, ofGetHeight(), 0, 0.1);
//    motionTrig.onThreshold = motionThresh;
//    motionTrig.offThreshold = motionThresh * 0.3;
//    sensitivity = maxiMap::linlin(touch.x, 0, ofGetWidth(), senseMin, senseMax);
}
void sceneAccelStretch::touchMoved(ofTouchEventArgs &touch) {
    
}
void sceneAccelStretch::touchUp(ofTouchEventArgs &touch) {
    
}
void sceneAccelStretch::touchDoubleTap(ofTouchEventArgs &touch) {
    
}

void sceneAccelStretch::beginScene() {
    sceneFingerStretch::beginScene();
    isPlaying = true;
}

void sceneAccelStretch::setMotionTriggering(bool newVal) {
    motionTriggering = newVal;
    updateTitle();
}
