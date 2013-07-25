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


#include "sceneLoop.h"


void sceneLoop::setup(sharedDataContainer *data) {
    looper = new EAVIGUI::LoopControl(this, 0, 0, 0, 1024, 1024, data);
    looper->setRelativePositioning(0.5, -looper->getScaledWidth() / 2.0, 0.5, -looper->getScaledHeight() / 2.0);
    interface.push_back(looper);

    baseScene::setup(data);
    grainPlayer = new grainPlayerType(&sharedData->buffer);
    position = 0;
    
}

void sceneLoop::update() {
    looper->setPos(position);
}

void sceneLoop::draw() {
    
}

void sceneLoop::audioRequested( float * output, int bufferSize, int nChannels ) {
    grainPlayer->setLoopStart(looper->start);
    grainPlayer->setLoopEnd(looper->end);
    for(int i =0; i < bufferSize; i++) {
        output[i] = grainPlayer->play(1, 1, 0.05, 2, 0.0);
    }
    position = grainPlayer->getNormalisedPosition();
}

void sceneLoop::audioIn( float * input, int bufferSize, int nChannels ) {
    
}

void sceneLoop::beginScene() {
    baseScene::beginScene();
    looper->updateWaveform(&sharedData->buffer);
}

void sceneLoop::endScene() {
    sharedData->loopStart = looper->start;
    sharedData->loopEnd = looper->end;
    baseScene::endScene();
}
