//
//  sceneLoopRecord.cpp
//  sonicTag2
//
//  Created by Chris Kiefer on 27/06/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#include <iostream>

#include "sceneLoopRecord.h"


void sceneLoopRecord::setup(sharedDataContainer *data) {
    baseScene::setup(data);
    clearCount = 0;
    isRecording = false;
    isPlaying = true;
    vis.setup(data);
    ofEnableSmoothing();
    ofEnableAlphaBlending();    
    ofSetCircleResolution(200);
}

void sceneLoopRecord::update() {
}

void sceneLoopRecord::draw() {
    if (isRecording){
        ofBackground(200, 128, 255);
    }
}

float sceneLoopRecord::getNextSample() {
    return sharedData->buffer.play(1);;
}


void sceneLoopRecord::audioRequested( float * output, int bufferSize, int nChannels ) {
    if(isPlaying > 0) {
        //play buffer
        for (int i=0; i < bufferSize; i++) {
            output[i] = getNextSample();
//            output[i] = compressor.compressor(output[i], 2, 0.7, 0.01, 0.99);
        }
    }else{
        memset(output, 0, sizeof(float) * bufferSize * nChannels);
    }

    //silence if recording
    if (isRecording) {
        memset(output, 0, sizeof(float) * bufferSize * nChannels);
    }
}

void sceneLoopRecord::audioIn( float * input, int bufferSize, int nChannels ) {
    float clearMult = clearCount > 0 ? 0 : 1;
    for (int i=0; i < bufferSize; i++) {
        float newSample = input[i] * clearMult;
        sharedData->buffer.loopRecord(fabs(newSample) < 0.001 ? 0 : newSample, isRecording, 0.5);
    }
    if (clearCount > 0) clearCount--;
}

void sceneLoopRecord::touchDown(ofTouchEventArgs &touch){
    isRecording = true;
    log::write(log::STARTRECORDING);
}

void sceneLoopRecord::touchMoved(ofTouchEventArgs &touch){
    
}

void sceneLoopRecord::touchUp(ofTouchEventArgs &touch){    
    isRecording = false;
    log::write(log::STOPRECORDING);
}

void sceneLoopRecord::touchDoubleTap(ofTouchEventArgs &touch){
    sharedData->buffer.clear();
    clearCount = 5;
    log::write(log::CLEARBUFFER);
}

void sceneLoopRecord::touchCancelled(ofTouchEventArgs &touch){
}

void sceneLoopRecord::beginScene() {
    baseScene::beginScene();
    if (sharedData->buffer.length == 0) {
        sharedData->buffer.setLength(maxiSettings::sampleRate * 2);
    }
    isRecording = false;
    clearCount = 0;
}

void sceneLoopRecord::endScene() {
    baseScene::endScene();
    isRecording = false;
}


