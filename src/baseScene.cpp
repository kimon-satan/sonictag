//
//  baseScene.cpp
//  sonicTag2
//
//  Created by Chris Kiefer on 27/06/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#include <iostream>

#include "baseScene.h"

EAIT::Counter<int> baseScene::objectIDCounter(700000);
EAIT::Counter<int> baseScene::sceneIDCounter(1000);


void baseScene::setup(sharedDataContainer *data) {
    sharedData = data;
    enabled = false;
    EAVIGUI::Label *title = new EAVIGUI::Label(this, objectIDCounter.next(), 10, 10, 700, 100, 
                                               &EAVIGUI::InterfaceManager::fontList["titles"],
                                               getTitle(),
                                               ofColor(0,255,0));
    title->setRelativePositioning(0.01, 0.01);
    title->setAnchorPoint(0, 0);
    interface.push_back(title);
    EAVIGUI::Label *subtitle = new EAVIGUI::Label(this, objectIDCounter.next(), 10, 10, 700, 100, 
                                               &EAVIGUI::InterfaceManager::fontList["subtitles"],
                                               getSubTitle(),
                                               ofColor(0,100,255));
    subtitle->setRelativePositioning(0.01, 0.95);
    subtitle->setAnchorPoint(0, 0);
    interface.push_back(subtitle);
    EAVIGUI::InterfaceManager::addObjects(interface);
    sceneID = sceneIDCounter.next();
    currentOrientation=1;
}

void baseScene::update() {
}

void baseScene::draw() {
    ofBackground(255);
    ofSetColor(255,255,255,255);
    
#ifdef TARGET_OF_IPHONE
    
//    if (currentOrientation==5 || currentOrientation==6) {
//        currentOrientation=prevoiusOrientation;
//    }
//
//    if (currentOrientation==1 || currentOrientation==0) {
//        ofPushMatrix();
//        ofTranslate(ofGetWidth()*0.5, ofGetHeight()*0.5);
//        sharedData->backdrop.setAnchorPercent(0.5, 0.5);
//        ofRotate(270);
//        sharedData->backdrop.draw(0, 0, ofGetWidth()*1.5, ofGetHeight()*1.5);
//        ofPopMatrix();
//
//    }
//    
//    if (currentOrientation==3) {
//        sharedData->backdrop.setAnchorPercent(0., 0.);
//        sharedData->backdrop.draw(0, 0, ofGetWidth(), ofGetHeight());
//    } 
//    
//    if (currentOrientation==2) {
//        ofPushMatrix();
//        ofTranslate(ofGetWidth()*0.5, ofGetHeight()*0.5);
//        sharedData->backdrop.setAnchorPercent(0.5, 0.5);
//        ofRotate(90);
//        sharedData->backdrop.draw(0, 0, ofGetWidth()*1.5, ofGetHeight()*1.5);
//        ofPopMatrix();
//
//    }
//    
//    if (currentOrientation==4) {
//        ofPushMatrix();
//        ofTranslate(0, 0);
//        ofRotate(180);
//        sharedData->backdrop.setAnchorPercent(1.0, 1.0);
//        sharedData->backdrop.draw(0, 0, ofGetWidth(), ofGetHeight());
//        ofPopMatrix();
//
//    } 
//    prevoiusOrientation = currentOrientation;
#else
    sharedData->backdrop.draw(0,0, ofGetWidth(), ofGetHeight());
#endif
    
}

void baseScene::audioRequested( float * output, int bufferSize, int nChannels ) {
    memset(output, 0, sizeof(float) * bufferSize * nChannels);    
}

void baseScene::audioIn( float * input, int bufferSize, int nChannels ) {
    
}

void baseScene::touchDown(ofTouchEventArgs &touch){
}

void baseScene::touchMoved(ofTouchEventArgs &touch){
    
}

void baseScene::touchUp(ofTouchEventArgs &touch){    
}

void baseScene::touchDoubleTap(ofTouchEventArgs &touch){
}
void baseScene::touchCancelled(ofTouchEventArgs &touch){
}

void baseScene::beginScene() {
    EAVIGUI::InterfaceManager::setGroupVisibility(interface, true);
    
}

void baseScene::endScene() {
    EAVIGUI::InterfaceManager::setGroupVisibility(interface, false);
    
}

string baseScene::getTitle() {
    return "<needs a title>";
}

string baseScene::getSubTitle() {
    return "<needs a subtitle>";
}

void baseScene::handleInterfaceEvent(int id, int eventTypeId, EAVIGUI::InterfaceObject *object) {
    
}

audioProcessor* baseScene::getAudioProcessor() {
    return new audioProcessor();
};

bool baseScene::canProgress() {
    return true;
}

void baseScene::onBarStart() {
    if (respondToBarChange.test()) {
        doBarChangeEvent();
    }
}

void baseScene::doBarChangeEvent() {
    
}
