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

#include "baseScene.h"
#include <algorithm>

EAIT::Counter<int> baseScene::objectIDCounter(700000);
EAIT::Counter<int> baseScene::sceneIDCounter(1000);


void baseScene::setup(sharedDataContainer *data) {
    sharedData = data;
    enabled = false;
    nbConnected = false;
//    string temptitle = getTitle();
//    std::replace(temptitle.begin(), temptitle.end(), '\n', ' ');
    title = new EAVIGUI::Label(this, objectIDCounter.next(), 10, 10, 700, 150,
                                               &EAVIGUI::InterfaceManager::fontList["titles"],
                                               "",
                                               ofColor(0,255,0));
    updateTitle();
    title->setRelativePositioning(0.01, 0.01);
    title->setAnchorPoint(0, 0);
    interface.push_back(title);

//    EAVIGUI::Label *subtitle = new EAVIGUI::Label(this, objectIDCounter.next(), 10, 10, 700, 100,
//                                               &EAVIGUI::InterfaceManager::fontList["subtitles"],
//                                               getSubTitle(),
//                                               ofColor(0,100,255));
//    subtitle->setRelativePositioning(0.01, 0.95);
//    subtitle->setAnchorPoint(0, 0);
//    interface.push_back(subtitle);

    EAVIGUI::InterfaceManager::addObjects(interface);
    sceneID = sceneIDCounter.next();
    currentOrientation=1;
    
    bleVals.resize(16);

}

void baseScene::update() {
}

void baseScene::draw() {
    ofBackground(255);
    ofSetColor(255,255,255,255);
    
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

void baseScene::updateTitle() {
    string temptitle = getTitle();
    std::replace(temptitle.begin(), temptitle.end(), '\n', ' ');
    title->setText(temptitle);
}


void baseScene::handleInterfaceEvent(int id, int eventTypeId, EAVIGUI::InterfaceObject *object) {
    switch(eventTypeId) {
        case EAVIGUI::InterfaceObject::TOUCHDOWN:
            ofSendMessage("temphidenav");
            break;
        case EAVIGUI::InterfaceObject::TOUCHUP:
            if (EAVIGUI::InterfaceManager::touchedObjectCount() == 0) {
                ofSendMessage("tempshownav");
            }
            break;
    }
}

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
