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

audioProcessorPlay::audioProcessorPlay() : audioProcessor() {
}

float audioProcessorPlay::play(float input) {
    float wave = sample->play();    
    return wave;
}


void scenePlay::setup(sharedDataContainer *data) {    
    headVis = new EAVIGUI::HeadVisualiser(this, objectIDCounter.next(), 0, 0);
    headVis->setRelativePositioning(0.5, 0.5);
    interface.push_back(headVis);
    
    baseScene::setup(data);
}

void scenePlay::update() {
    float env = sharedData->currSampleInstance->mir.env.getEnv();
    headVis->setScale(2.0 + env * 2.0);
}

void scenePlay::draw() {
    baseScene::draw();
    ofSetCircleResolution(200);
//    ofBackground(255, 255, 255);
}

void scenePlay::touchDown(ofTouchEventArgs &touch){
    sharedData->currSampleInstance->sample.trigger();
}


void scenePlay::touchUp(ofTouchEventArgs &touch){   
}

void scenePlay::beginScene() {
    headVis->setImage(&sharedData->currSampleInstance->icon);
    headVis->setRelativePositioning(0.5, -sharedData->currSampleInstance->icon.width / 2.0, 0.5, -sharedData->currSampleInstance->icon.height / 2.0);
    headVis->setScale(3.0);
    baseScene::beginScene();
    pos = 0;
    playing = false;    
    
}

void scenePlay::endScene() {
    baseScene::endScene();
    playing = false;
}

