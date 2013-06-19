//
//  scenePlay.cpp
//  sonicTag2
//
//  Created by Chris Kiefer on 27/06/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#include <iostream>
#include "scenePlay.h"
#include <sstream>
#include "audioCatalogue.h"

void scenePlay::setup(sharedDataContainer *data) {
    
    mfccVis = new EAVIGUI::MfccVisualiser(this, VISUALISER, 0, 0, ofGetHeight(), ofGetHeight(), data);
    mfccVis->setRelativePositioning(0.5, -mfccVis->getScaledWidth() / 2.0, 0.5, -mfccVis->getScaledHeight() / 2.0);
    interface.push_back(mfccVis);

    histBackBtn = (new EAVIGUI::ImageButton(this, HISTBACK, 0, 0, "undo.png", "undo.png"));
    histBackBtn->setRelativePositioning(0.25, 0, 0.1, 0);
    histBackBtn->setAnchorPoint(0, 0);
    histBackBtn->fadeTime = 100;
    interface.push_back(histBackBtn);

    histForwardBtn = (new EAVIGUI::ImageButton(this, HISTFORWARD, 0, 0, "redo.png", "redo.png"));
    histForwardBtn->setRelativePositioning(0.75, -histForwardBtn->getScaledWidth(), 0.1, 0);
    histForwardBtn->setAnchorPoint(0, 0);
    histForwardBtn->fadeTime = 100;
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
                output[i] = sharedData->buffer.play();
            }else{
                output[i] = sharedData->buffer.playOnce();
            }
//            output[i] = compressor.compressor(output[i], 2, 0.7, 0.01, 0.99);

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
                    break;
                case HISTFORWARD:
                    playing = false;
                    sharedData->buffer.load(audioCatalogue::nextRecording());
                    sharedData->randomiseColours();
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
        sharedData->buffer.trigger();
        if (loop)
            cout << "Loop\n";
    }
    
}


void scenePlay::setLooped(bool newValue) {
    loop = newValue;
    updateTitle();
}
