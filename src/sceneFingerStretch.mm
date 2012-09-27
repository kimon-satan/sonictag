//
//  sceneFingerStretch.cpp
//  sonicTag2
//
//  Created by Chris Kiefer on 28/06/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#include <iostream>
#include "sceneFingerStretch.h"
#include <cmath>


void sceneFingerStretch::setup(sharedDataContainer *data) {
    surface = new EAVIGUI::RadialScratchSurface(this, objectIDCounter.next(), 0, 0, ofGetWidth(), ofGetWidth());
    surface->setRelativePositioning(0.5, -ofGetWidth()/2.0, 0.5, -ofGetWidth()/2.0);
    surface->setAnchorPoint(0.5, 0.5);
    interface.push_back(surface);
    velMA.resize(5);
    velMA.fillWith(0);
    scenePlay::setup(data);
    
}


void sceneFingerStretch::handleInterfaceEvent(int id, int eventTypeId, EAVIGUI::InterfaceObject *object) {
    scenePlay::handleInterfaceEvent(id, eventTypeId, object);
//    cout << id << ", " << eventTypeId << endl;
    switch(eventTypeId) {
        case EAVIGUI::InterfaceObject::TOUCHMOVED:
            if (surface->id == id) {
                velMA.addSample(surface->getVelocity() * 5.0);
                ((audioProcessorTimeStretch*)currAudioProcessor)->stretch = velMA.value();
                cout << velMA.value() << endl;
            }
            break;
        case EAVIGUI::InterfaceObject::TOUCHUP:
            if (surface->id == id) {
                velMA.addSample(surface->getVelocity() * 5.0);
                float snapVal=velMA.value();
                if (snapVal < 1.0) {
                    //snap down to 1/16?
                    float newVal = 1.0f / 16.0f;
                    for(int s=8; s >= 1; s /= 2) {
                        if (snapVal < newVal) {
                            break;
                        }
                        newVal = 1.0f / (float) s;
                    }
                    snapVal = newVal;
                }else{
                    //or snap to int
                    snapVal = floor(snapVal + 0.5f);
                    snapVal = min(snapVal, 4.0f);
                }
//                cout << velMA.value() << "Snap: " << snapVal << endl;
                respondToBarChange.set();
                
                ((audioProcessorTimeStretch*)currAudioProcessor)->stretch = snapVal;
            }
            break;
    }
}

void sceneFingerStretch::doBarChangeEvent() {
    cout << "Do bar change\n";
    ofSendMessage("resync");
}

void sceneFingerStretch::beginScene() {
    scenePlay::beginScene();
    respondToBarChange.set();
}

void sceneFingerStretch::endScene() {
    scenePlay::endScene();
    respondToBarChange.set();
}
