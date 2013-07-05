//
//  sceneFilterPlay.h
//  sonicTag2NB
//
//  Created by Chris on 12/03/2013.
//
//

#ifndef __sonicTag2NB__sceneFilterPlay__
#define __sonicTag2NB__sceneFilterPlay__

#include <iostream>
#include "baseScene.h"
#include "ofxMaxim.h"
#include <vector>
#include "visualiser.h"
#include "geomFunctions.h"
#include "EAIT.h"
#include "baseScene.h"
#include "RadialScratchSurface.h"

using namespace std;

class sceneFilterPlay : public baseScene {
public:
    void setup(sharedDataContainer *data);
    void update();
    void audioRequested( float * output, int bufferSize, int nChannels );
    void beginScene();
    void endScene();
    string getTitle() {return string("Filter Play");}
//    void updateBLEVals(vector<float> newVals);
    void handleInterfaceEvent(int id, int eventTypeId, EAVIGUI::InterfaceObject *object);
protected:
    maxiSVF filt;
    float sigAvg;
    EAVIGUI::RadialScratchSurface *surface;
    float freq,res;
private:
    
};





#endif /* defined(__sonicTag2NB__sceneFilterPlay__) */
