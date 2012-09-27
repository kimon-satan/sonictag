//
//  sceneGain.cpp
//  DRSApp
//
//  Created by Chris Kiefer on 31/07/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#include <iostream>
#include "sceneGain.h"

void sceneGain::setup(sharedDataContainer *data) {
    dial = new EAVIGUI::CircularDial(this, objectIDCounter.next(), 0, 0, 500, 500);
    dial->setRelativePositioning(0.5, -dial->getScaledWidth() / 2.0, 0.5, -dial->getScaledHeight() / 2.0);
    interface.push_back(dial);

    scenePlay::setup(data);
}

void sceneGain::setAudioProcessor(audioProcessor* currProcessor) {
    scenePlay::setAudioProcessor(currProcessor);
    dial->setValue(((audioProcessorGain*)currProcessor)->amp);
    cout << "Dial: " << dial->getValue() << endl;
}


void sceneGain::handleInterfaceEvent(int id, int eventTypeId, EAVIGUI::InterfaceObject *object) {
    scenePlay::handleInterfaceEvent(id, eventTypeId, object);
    switch(eventTypeId) {
        case EAVIGUI::InterfaceObject::TOUCHMOVED:
            if (dial->id == id) {
                ((audioProcessorGain*)currAudioProcessor)->amp = dial->getValue();
            }
            break;
    }
}
