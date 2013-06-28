//
//  sceneLoop.cpp
//  SonicTag3
//
//  Created by Chris on 28/06/2013.
//
//

#include "sceneLoop.h"


void sceneLoop::setup(sharedDataContainer *data) {
    looper = new EAVIGUI::LoopControl(this, 0, 0, 0, 500, 500, data);
    looper->setRelativePositioning(0.5, -looper->getScaledWidth() / 2.0, 0.5, -looper->getScaledHeight() / 2.0);
    interface.push_back(looper);

    baseScene::setup(data);
    grainPlayer = new grainPlayerType(&sharedData->buffer);
    
}

void sceneLoop::draw() {
    
}

void sceneLoop::audioRequested( float * output, int bufferSize, int nChannels ) {
    grainPlayer->setLoopStart(looper->start);
    grainPlayer->setLoopEnd(looper->end);
    for(int i =0; i < bufferSize; i++) {
        output[i] = grainPlayer->play(1, 1, 0.05, 2, 0.0);
    }
}

void sceneLoop::audioIn( float * input, int bufferSize, int nChannels ) {
    
}


