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
}

void sceneFingerPitch::doBarChangeEvent() {
    //do nothing
}

float sceneFingerPitch::getNextSample() {
    return pitchStretch->play(maxiMap::linlin(velocity, 0, 120, 0.1, 2.0), 1, 0.05, 2, 0.0);
}

