//
//  sceneVBirth.cpp
//  DRSApp
//
//  Created by Chris Kiefer on 26/07/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#include <iostream>
#include "sceneVBirth.h"
#include <sstream>

void sceneVBirth::setup(sharedDataContainer *data) {
    
    firstRun = true;
    maxTracks = 14;
    headRadius.resize(maxTracks);
    mixLevels.resize(maxTracks);
    
    mapIcon = new EAVIGUI::ImageButton(this, objectIDCounter.next(), 0, 0, "mapicon.png");
    mapIcon->setRelativePositioning(0.02, 0, 0.90, -mapIcon->getScaledHeight());
//    mapIcon->setVisible(true);
    interface.push_back(mapIcon);

    for(int i=1; i <= maxTracks; i++) {
        stringstream fileroot;
        fileroot << "deanheads/DFE---d";
        fileroot << 1 << ".png";
        EAVIGUI::ImageButton *head = new EAVIGUI::ImageButton(this, objectIDCounter.next(), 0, 0, fileroot.str());
        head->setColor(ofColor(255,255,255,255));
        head->fadeTime=0;
        heads.push_back(head);
        interface.push_back(head);
        headRadius[i-1].resize(30);
        headRadius[i-1].fillWith(0);        
        mixLevels[i-1].resize(30);
        mixLevels[i-1].fillWith(1.0);        
    }

    
    instructions = new EAVIGUI::Label(this, objectIDCounter.next(), 0, 0, 600, 600,
                                      &EAVIGUI::InterfaceManager::fontList["c64Rounded"],
                                      "",
                                      ofColor(205, 105, 201));
    instructions->setRelativePositioning(0.5, -instructions->getScaledWidth() / 2.0, 0.5, -instructions->getScaledHeight() / 2.0);
    instructions->setText("Welcome to the \nDean Rodney Singers App!\n\n"
                          "Each icon represents a \ndifferent part of a song.\n"
                          "Select a part and navigate \nthrough the different screens \n"
                          "to remix it.\n\n"
                          "Tap on the figure on the \nbottom right to return here \n"
                          "and choose another part.\n"
                          "\n\nTap to continue...");
    instructions->backgroundColour = ofColor(50, 50, 50, 240);
    instructions->setIsInteractive(true);
    instructionsModal.push_back(instructions);
    
    baseScene::setup(data);
    EAVIGUI::InterfaceManager::addObjects(instructionsModal);
}

void sceneVBirth::setupNewTrack() {
    envs.resize(sharedData->audioTracks.size());
    for(int i=0; i < envs.size(); i++) {
        envs[i].setAttack(100);
        envs[i].setRelease(100);
    }
    int numIcons = assets::dimensions[sharedData->currentDimension].icons.size();
    for(int i=0; i < sharedData->audioTracks.size(); i++) {
        stringstream fileroot;
        fileroot << "icons/" << assets::dimensions[sharedData->currentDimension].folder << "/";
        fileroot << assets::dimensions[sharedData->currentDimension].icons[i % numIcons] << ".png";
        cout << ofToDataPath(fileroot.str()) << endl;
        heads[i]->loadNewImage(ofToDataPath(fileroot.str()));        
    }
    setHeadPositions();
    
    currTrack = -1;
    
    
}


void sceneVBirth::setHeadPositions() {
    float angleInc = TWO_PI / (float) sharedData->audioTracks.size();
    for(int i=0; i < sharedData->audioTracks.size(); i++) {
        float xPos, yPos;
        yPos = sin(angleInc * (i-1)) * (ofGetWidth() * 0.3 * headRadius[i].value());
        xPos = cos(angleInc * (i-1)) * (ofGetWidth() * 0.3 * headRadius[i].value());
        heads[i]->setRelativePositioning(0.5, (-heads[i]->getWidth() / 2.0) + xPos, 0.5, (-heads[i]->getHeight() / 2.0) + yPos);
    }
}

void sceneVBirth::update() {
//    cout << mixLevels.size() << ", " << heads.size() << endl;
    for(int i=0; i < sharedData->audioTracks.size(); i++) {
//        heads[i]->setColor(ofColor(255,255,255,amps[i].value() * 255.0));
        heads[i]->setScale((envs[i].getEnv() * 1.2) + 0.9);
        headRadius[i].addSample(i == currTrack ? 0.0 : 1.0);
        mixLevels[i].addSample(-1 == currTrack ? 1.0 : i == currTrack ? 1.0 : 0.1);
//        mixLevels[i] = mix[i].value();
    }
//    for(int i=sharedData->audioTracks.size(); i <= 11; i++) {
    setHeadPositions();
}

void sceneVBirth::draw() {
    baseScene::draw();
}

void sceneVBirth::audioRequested( float * output, int bufferSize, int nChannels ) {
    baseScene::audioRequested(output, bufferSize, nChannels);
    if (sharedData->audioLoaded) {
        for(int i=0; i < bufferSize; i++) {
            float wave=0;
            float totalAmp = 0.0;
            for(int j=0; j < sharedData->audioTracks.size(); j++) {
                float samp = sharedData->audioTracks[j].play();
                wave += (samp * mixLevels[j].value());
                envs[j].play(samp);
                totalAmp += mixLevels[j].value();
            }
//            wave /= totalAmp == 0 ? 1.0: totalAmp;
#ifdef TARGET_OF_IPHONE
            //limiter
            if (wave > 0.99) {
                wave = 0.99;
            }else if (wave < -0.99) {
                wave = -0.99;
            }
#endif
            output[i] = wave; //* sharedData->currSong->gain;
        }
    }
}

void sceneVBirth::audioIn( float * input, int bufferSize, int nChannels ) {
    
}

void sceneVBirth::touchDown(ofTouchEventArgs &touch) {
    
}

void sceneVBirth::touchMoved(ofTouchEventArgs &touch) {
    
}

void sceneVBirth::touchUp(ofTouchEventArgs &touch) {
    
}

void sceneVBirth::touchDoubleTap(ofTouchEventArgs &touch) {
    
}

void sceneVBirth::touchCancelled(ofTouchEventArgs &touch) {
    
}

void sceneVBirth::beginScene() {
    baseScene::beginScene();
    for(int i=0; i < heads.size(); i++) {
        heads[i]->setVisible(false);
    }
    for(int i=0; i < sharedData->audioTracks.size(); i++) {
        heads[i]->setVisible(true);
    }
    
    if(firstRun)
        EAVIGUI::InterfaceManager::showHideModalGroup(&instructionsModal, true);
}

void sceneVBirth::endScene() {
    baseScene::endScene();
    firstRun = false;
    instructions->fadeTime = 0;

}

int sceneVBirth::getNewAudioTrackNumber() {
    int sampleIndex = -1 == currTrack ? 0 : currTrack; 
    return sampleIndex;
}

ofImage sceneVBirth::getHead(int headId) {
    return heads[headId]->getImage();
}
string sceneVBirth::getTitle() {
    return "Choose a track!";
}

void sceneVBirth::handleInterfaceEvent(int id, int eventTypeId, EAVIGUI::InterfaceObject *object) {
    baseScene::handleInterfaceEvent(id, eventTypeId, object);
    switch(eventTypeId) {
        case EAVIGUI::InterfaceObject::TOUCHUP:
            if (instructions->id == id) {
                EAVIGUI::InterfaceManager::showHideModalGroup(&instructionsModal, false);
            }else if (mapIcon->id == id) {
                ofSendMessage("map");
            }else{
                int headID = (id - heads[0]->id);
                currTrack = (currTrack == headID) ? -1 : headID;
                cout << "head id : " << headID << ", " << currTrack << endl;
            }
            break;
    }
    
}

bool sceneVBirth::canProgress() {
    return currTrack != -1;
}

