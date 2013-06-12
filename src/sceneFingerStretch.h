//
//  sceneFingerStretch.h
//  sonicTag2
//
//  Created by Chris Kiefer on 28/06/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#ifndef sonicTag2_sceneFingerStretch_h
#define sonicTag2_sceneFingerStretch_h

#include "RadialScratchSurface.h"
#include "DRSGrains.h"
#include "sceneFingerPlay.h"

typedef DRSmaxiPitchStretch<float, DRShannWinFunctor<float> > grainPlayerType;




class sceneFingerStretch : public sceneFingerPlay {
public:
    void setup(sharedDataContainer *data);
    float getNextSample();
    string getTitle() {return "Time Stretch";}
    void beginScene();
protected:
    grainPlayerType *pitchStretch;
};

#endif
