//
//  sceneFingerPlayPitch.h
//  sonicTag2
//
//  Created by Chris Kiefer on 05/07/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#ifndef sonicTag2_sceneFingerPlayPitch_h
#define sonicTag2_sceneFingerPlayPitch_h

#include "sceneFingerPlay.h"
#include "EAIT.h"
#include "geomFunctions.h"

class sceneFingerPlayPitch : public sceneFingerPlay {
public:
    void setup(sharedDataContainer *data);
    void update();
    void touchMoved(ofTouchEventArgs &touch);
    float angularVelocity, angle, lastAngle;
    float getNextSample();
    string getTitle() {return "Pitch Scratch";}
    EAIT::MovingAverageF velMA;
};

#endif
