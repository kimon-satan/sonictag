//
//  sceneAccelPitch.h
//  sonicTag2
//
//  Created by Chris Kiefer on 06/07/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#ifndef sonicTag2_sceneAccelPitch_h
#define sonicTag2_sceneAccelPitch_h

#include "sceneAccelStretch.h"

class sceneAccelPitch : public sceneAccelStretch {
public:
    float getNextSample();
//    string getTitle() {return "Motion Pitch Modulation";}            
    string getTitle() {return string("Motion -> Pitch").append(motionTriggering ? " (trig)" : "");}        
};

#endif
