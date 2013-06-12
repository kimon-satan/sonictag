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
    mfccVis = new EAVIGUI::MfccVisualiser(this, objectIDCounter.next(), 0, 0, ofGetHeight(), ofGetHeight(), data);
    mfccVis->setRelativePositioning(0.5, -mfccVis->getScaledWidth() / 2.0, 0.5, -mfccVis->getScaledHeight() / 2.0);
    interface.push_back(mfccVis);

    sceneLoopRecord::setup(data);
    sharedData->buffer.reset();
}

void sceneFingerPlay::audioIn( float * input, int bufferSize, int nChannels ) {
    //no recording
}

void sceneFingerPlay::update() {
    sceneLoopRecord::update();
    if (opx != px && opy != py) {
        velocity = ofDist(opx,opy,px,py);
        velX = fabs(px - opx);
        velY = fabs(py - opy);
        opx = px;
        opy = py;
        isPlaying = true;
        onCounter=10;
    }else {
        onCounter--;
        if (onCounter <= 0)
            isPlaying = false;
    }
}

void sceneFingerPlay::draw() {
    sceneLoopRecord::draw();
    if (isPlaying) {
        ofFill();
        ofSetColor(0, 200, 0, 150);
        ofCircle(px, py, 40);
    }
}

void sceneFingerPlay::touchDown(ofTouchEventArgs &touch) {
    
}

void sceneFingerPlay::touchMoved(ofTouchEventArgs &touch) {
    if (0 == touch.id) {
        px = touch.x;
        py = touch.y;
        log::write(log::TOUCHCOORDS, px, py);
    }
}

void sceneFingerPlay::touchUp(ofTouchEventArgs &touch) {
}

void sceneFingerPlay::touchDoubleTap(ofTouchEventArgs &touch) {
    //do nothing
}



void sceneFingerPlay::beginScene() {
    sceneLoopRecord::beginScene();
    isPlaying = false;
    opx = opy = px = py = 0;
    onCounter = 0;
}

void sceneFingerPlay::endScene() {
    sceneLoopRecord::endScene();
}
