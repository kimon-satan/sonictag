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
#include "scenePlay.h"
#include <sstream>
#include "audioCatalogue.h"

void scenePlay::setup(sharedDataContainer *data) {
    
    mfccVis = new EAVIGUI::MfccVisualiser(this, VISUALISER, 0, 0, ofGetHeight(), ofGetHeight(), data);
    mfccVis->setRelativePositioning(0.5, -mfccVis->getScaledWidth() / 2.0, 0.5, -mfccVis->getScaledHeight() / 2.0);
    interface.push_back(mfccVis);

    histBackBtn = (new EAVIGUI::ImageButton(this, HISTBACK, 0, 0, "undo.png", "undoTD.png"));
    histBackBtn->setRelativePositioning(0.25, 0, 0.1, 0);
    histBackBtn->setAnchorPoint(0, 0);
    histBackBtn->fadeTime = 100;
    histBackBtn->setCanTouchTranparency(true);
    interface.push_back(histBackBtn);

    histForwardBtn = (new EAVIGUI::ImageButton(this, HISTFORWARD, 0, 0, "redo.png", "redoTD.png"));
    histForwardBtn->setRelativePositioning(0.75, -histForwardBtn->getScaledWidth(), 0.1, 0);
    histForwardBtn->setAnchorPoint(0, 0);
    histForwardBtn->fadeTime = 100;
    histForwardBtn->setCanTouchTranparency(true);
    interface.push_back(histForwardBtn);

    baseScene::setup(data);
    
    loop = false;
    prevButtonCentre.x = ofGetWidth() / 4;
    nextButtonCentre.x = ofGetWidth() / 4 * 3;
    prevButtonCentre.y = nextButtonCentre.y = 150;
    
    undo.loadImage("undo.png");
    redo.loadImage("redo.png");
    
    undoPos.x = ofGetWidth()/4.0 - undo.width / 2.0;
    undoPos.y = 70;
    redoPos.x = ofGetWidth()/4.0*3.0 - undo.width / 2.0;
    redoPos.y = 70;
    
    showUndoRedo = false;
    nbEnergyTrigger = EAIT::BasicTriggerF(0.05, 0.03, 20);

}


void scenePlay::updateBLEVals(vector<float> newVals, float sigAvg) {
    cout << sigAvg << endl;
    nbEnergyTrigger.newFrame(sigAvg);
    if (nbEnergyTrigger.justTriggered()) {
        cout << "Trig" << endl;
        play();
    }
}

void scenePlay::update() {
}

void scenePlay::draw() {
    ofSetCircleResolution(200);
    ofBackground(255, 255, 255);
    ofSetColor(255,255,255);
    if (showUndoRedo) {
        undo.draw(ofGetWidth()/4.0 - undo.width / 2.0, 70);
        redo.draw(ofGetWidth()/4.0*3.0 - redo.width / 2.0, 70);
    }
    
}

void scenePlay::audioRequested( float * output, int bufferSize, int nChannels ) {
    memset(output, 0, sizeof(float) * bufferSize * nChannels);
    if (playing) {
        for(int i=0; i<bufferSize; i++) {
            if (loop) {
                output[i] = sharedData->buffer.playLoop(sharedData->loopStart, sharedData->loopEnd);
            }else{
                output[i] = sharedData->buffer.playUntil(sharedData->loopEnd);
            }
        }
    }
}

void scenePlay::audioIn( float * input, int bufferSize, int nChannels ) {
}

void scenePlay::touchDown(ofTouchEventArgs &touch){
}


void scenePlay::touchUp(ofTouchEventArgs &touch){
}

void scenePlay::beginScene() {
    baseScene::beginScene();
    pos = 0;
    playing = false;
}

void scenePlay::endScene() {
    baseScene::endScene();
    playing = false;
}

void scenePlay::setUndoRedoVisibility(bool show) {
    showUndoRedo = show;
}


void scenePlay::handleInterfaceEvent(int id, int eventTypeId, EAVIGUI::InterfaceObject *object) {
    cout << "event: " << id << endl;
    switch(eventTypeId) {
        case EAVIGUI::InterfaceObject::TOUCHDOWN:
            switch(id) {
                case HISTBACK:
                    playing = false;
                    sharedData->buffer.load(audioCatalogue::prevRecording());
                    sharedData->randomiseColours();
                    sharedData->loopStart = 0.0;
                    sharedData->loopEnd = 1.0;
                    break;
                case HISTFORWARD:
                    playing = false;
                    sharedData->buffer.load(audioCatalogue::nextRecording());
                    sharedData->randomiseColours();
                    sharedData->loopStart = 0.0;
                    sharedData->loopEnd = 1.0;
                    break;
            };
            break;
        case EAVIGUI::InterfaceObject::TOUCHUP:
            switch(id) {
                case VISUALISER:
                    play();
                    break;
            };
            break;
        
    }
}

void scenePlay::play() {
    if (loop) {
        if (playing) {
            playing = false;
        }else{
            pos = 0;
            playing = true;
            cout << "Playing\n";
            sharedData->buffer.trigger();
            if (loop)
                cout << "Loop\n";
        }
    }else{
        pos = 0;
        playing = true;
        cout << "Playing\n";
        sharedData->buffer.setPosition(sharedData->loopStart);
        if (loop)
            cout << "Loop\n";
    }
    
}


void scenePlay::setLooped(bool newValue) {
    loop = newValue;
    updateTitle();
}
