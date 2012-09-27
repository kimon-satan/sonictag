//
//  sceneFilter.cpp
//  DRSApp
//
//  Created by Chris Kiefer on 01/08/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#include <iostream>

#include "sceneFilter.h"

void sceneFilter::setAudioProcessor(audioProcessor* currProcessor) {
    scenePlay::setAudioProcessor(currProcessor);
    dial->setValue(maxiMap::explin(((audioProcessorFilter*)currProcessor)->freq, 20, 15000, 0.01, 1));
    cout << "Dial: " << dial->getValue() << endl;
}


void sceneFilter::handleInterfaceEvent(int id, int eventTypeId, EAVIGUI::InterfaceObject *object) {
    scenePlay::handleInterfaceEvent(id, eventTypeId, object);
    switch(eventTypeId) {
        case EAVIGUI::InterfaceObject::TOUCHMOVED:
            if (dial->id == id) {
                ((audioProcessorFilter*)currAudioProcessor)->freq = maxiMap::linexp(dial->getValue(), 0.01, 1, 20, 15000);
                ((audioProcessorFilter*)currAudioProcessor)->res = maxiMap::linlin(dial->getValue(), 0, 1, 20, 1);
            }
            break;
    }
}
