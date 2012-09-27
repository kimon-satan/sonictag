//
//  sceneDistort.cpp
//  DRSApp
//
//  Created by Chris Kiefer on 01/08/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#include <iostream>
#include "sceneDistort.h"

void sceneDistort::setAudioProcessor(audioProcessor* currProcessor) {
    scenePlay::setAudioProcessor(currProcessor);
    dial->setValue(maxiMap::linlin(((audioProcessorDistort*)currProcessor)->level, 1, 5, 0, 1));
    cout << "Dial: " << dial->getValue() << endl;
    
}


void sceneDistort::handleInterfaceEvent(int id, int eventTypeId, EAVIGUI::InterfaceObject *object) {
    scenePlay::handleInterfaceEvent(id, eventTypeId, object);
    switch(eventTypeId) {
        case EAVIGUI::InterfaceObject::TOUCHMOVED:
            if (dial->id == id) {
                ((audioProcessorDistort*)currAudioProcessor)->level = maxiMap::linlin(dial->getValue(), 0, 1, 1, 10);
            }
            break;
    }
}
