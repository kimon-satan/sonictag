//
//  sceneFingerPitch.cpp
//  sonicTag2
//
//  Created by Chris Kiefer on 28/06/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#include <iostream>
#include "sceneFingerPitch.h"

void sceneFingerPitch::handleInterfaceEvent(int id, int eventTypeId, EAVIGUI::InterfaceObject *object) {
    scenePlay::handleInterfaceEvent(id, eventTypeId, object);
    switch(eventTypeId) {
        case EAVIGUI::InterfaceObject::TOUCHMOVED:
            if (surface->id == id) {
                velMA.addSample(MIN(surface->getVelocity() * 5.0, 4.0));
//                ((audioProcessorTimeStretch*)sharedData->currSampleInstance->audioFlow[0])->pitch = velMA.value();
            }
            break;
        case EAVIGUI::InterfaceObject::TOUCHUP:
            break;
    }
}

void sceneFingerPitch::doBarChangeEvent() {
    //do nothing
}
