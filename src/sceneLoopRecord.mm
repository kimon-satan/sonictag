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
    return sharedData->buffer.playLoop(sharedData->loopStart, sharedData->loopEnd);
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
        sharedData->buffer.loopRecord(fabs(newSample) < 0.001 ? 0 : newSample, isRecording, 0.5, sharedData->loopStart, sharedData->loopEnd);
    }
    if (clearCount > 0) clearCount--;
}

void sceneLoopRecord::touchDown(ofTouchEventArgs &touch){
    isRecording = true;
    sharedData->soundRecorded = true;    
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
    sharedData->buffer.trigger();
    
    isRecording = false;
    clearCount = 0;
    
}

void sceneLoopRecord::endScene() {
    baseScene::endScene();
    isRecording = false;
}


