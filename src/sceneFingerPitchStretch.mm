//
//  sceneFingerPitchStretch.cpp
//  sonicTag2
//
//  Created by Chris Kiefer on 28/06/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#include <iostream>
#include "sceneFingerPitchStretch.h"

float sceneFingerPitchStretch::getNextSample() {
    return pitchStretch->play(maxiMap::linlin(velX, 0, 120, 0.1, 2.0), maxiMap::linlin(velY, 0, 120, 0.1, 2.0), 0.05, 2, 0.0);
    return 0;
}
