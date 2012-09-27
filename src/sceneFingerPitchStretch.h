//
//  sceneFingerPitchStretch.h
//  sonicTag2
//
//  Created by Chris Kiefer on 28/06/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#ifndef sonicTag2_sceneFingerPitchStretch_h
#define sonicTag2_sceneFingerPitchStretch_h

#include "sceneFingerPitch.h"

class sceneFingerPitchStretch : public sceneFingerPitch {
public:
    float getNextSample();
    string getTitle() {return "Pitch and Time Stretch";}    
    
protected:
};


#endif
