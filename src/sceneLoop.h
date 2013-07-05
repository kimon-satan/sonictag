//
//  sceneLoop.h
//  SonicTag3
//
//  Created by Chris on 28/06/2013.
//
//

#ifndef __SonicTag3__sceneLoop__
#define __SonicTag3__sceneLoop__

#include <iostream>
#include "baseScene.h"
#include "loopControl.h"
#include "DRSGrains.h"

typedef DRSmaxiPitchStretch<float, DRShannWinFunctor<float> > grainPlayerType;

class sceneLoop: public baseScene {
public:
    void setup(sharedDataContainer *data);
    void draw();
    string getTitle() {return string("Loop Points");}
    void audioRequested( float * output, int bufferSize, int nChannels );
    void audioIn( float * input, int bufferSize, int nChannels );
    void beginScene();
    void endScene();
    void update();
protected:
    EAVIGUI::LoopControl *looper;
    grainPlayerType *grainPlayer;
    float position;
    
};

#endif /* defined(__SonicTag3__sceneLoop__) */
