//
//  sceneAccelPitchStretch.h
//  sonicTag2
//
//  Created by Chris Kiefer on 06/07/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#ifndef sonicTag2_sceneAccelPitchStretch_h
#define sonicTag2_sceneAccelPitchStretch_h

#include "sceneAccelStretch.h"

class sceneAccelPitchStretch : public sceneAccelStretch {
public:
    float getNextSample();
//    string getTitle() {return "Motion Pitch and Time Stretch";}                
    string getTitle() {return string("Motion Stretch \nAll").append(motionTriggering ? "\n(trig)" : "");}        
};

#endif
