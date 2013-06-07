//
//  sceneFingerPlay.cpp
//  sonicTag2
//
//  Created by Chris Kiefer on 28/06/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#include <iostream>

#include "sceneFingerPlay.h"

void sceneFingerPlay::setup(sharedDataContainer *data) {
    headVis = new EAVIGUI::HeadVisualiser(this, objectIDCounter.next(), 0, 0);
    headVis->setRelativePositioning(0.5, 0.5);
    interface.push_back(headVis);

    baseScene::setup(data);
    sharedData->buffer.reset();
    envf.setAttack(10);
    envf.setRelease(10);
    
    angularVelocity = 0.0;
    lastAngle = 0;
    velMA.resize(10);
    opx = ofGetWidth()/2.0;
    opy = ofGetHeight()/2.0;
    isPlaying = false;

}


float sceneFingerPlay::getNextSample() {
//    return sharedData->currSampleInstance->sample.play();
    return 0;
}

void sceneFingerPlay::audioRequested( float * output, int bufferSize, int nChannels ) {
    if (isPlaying) {
        for(int i=0; i<bufferSize; i++) {
            output[i] = getNextSample();
            envf.play(output[i]);
        }
    }else{
        memset(output, 0, sizeof(float) * bufferSize * nChannels);                
    }
}

void sceneFingerPlay::update() {
    headVis->setScale(3.0 + envf.getEnv() * 2.0);
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

void sceneFingerPlay::draw() {
    baseScene::draw();
    ofBackground(255);
    ofFill();
    ofSetColor(0, 200, 0, 150);
    ofCircle(px, py, 40);
}

void sceneFingerPlay::touchDown(ofTouchEventArgs &touch) {
    processTouch(touch);
}

void sceneFingerPlay::touchMoved(ofTouchEventArgs &touch) {
    processTouch(touch);
}

void sceneFingerPlay::processTouch(ofTouchEventArgs &touch) {
    if (0 == touch.id) {
        px = touch.x;
        py = touch.y;
        angle = geom::angleBetween(px, py, ofGetWidth()/2.0, ofGetHeight()/2.0) + PI;
        log::write(log::ANGLE, angle);
    }        
}


void sceneFingerPlay::touchUp(ofTouchEventArgs &touch) {
}

void sceneFingerPlay::touchDoubleTap(ofTouchEventArgs &touch) {
}



void sceneFingerPlay::beginScene() {
    baseScene::beginScene();
    isPlaying = false;
    opx = opy = px = py = 0;
    onCounter = 0;
}

void sceneFingerPlay::endScene() {
    baseScene::endScene();
}
