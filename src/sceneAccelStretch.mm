//
//  sceneAccelStretch.cpp
//  sonicTag2
//
//  Created by Chris Kiefer on 06/07/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

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
//    senseMin = 0.1;
//    senseMax = 2.0;
}

void sceneAccelStretch::draw() {
//    ofBackground(255,255,255);
//    ofSetColor(200,200,200,100);
//    if (motionTriggering) {
//        float yLine = maxiMap::linlin(motionThresh, 0, 0.1, 0, ofGetHeight());
//        ofLine(0, yLine, ofGetWidth(), yLine);
//    }
//    float xLine = maxiMap::linlin(sensitivity, senseMin, senseMax, 0, ofGetWidth());
//    ofLine(xLine, 0, xLine, ofGetHeight());
    
}

//void sceneAccelStretch::setThreshold(float thresh) {
//    motionThresh = thresh;
//    motionTrig.onThreshold = motionThresh;
//    motionTrig.offThreshold = motionThresh * 0.9;
//    motionTrig.reset();
//}

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
