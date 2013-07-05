//
//  sceneFXPlay1.h
//  sonicTag2NB
//
//  Created by Chris on 13/03/2013.
//
//

#ifndef __sonicTag2NB__sceneFXPlay1__
#define __sonicTag2NB__sceneFXPlay1__

#include <iostream>
#include "sceneFilterPlay.h"

using namespace std;

class sceneFXPlay1 : public sceneFilterPlay {
public:
    void audioRequested( float * output, int bufferSize, int nChannels );
    string getTitle() {return string("Ring \nModulator");}
//    void updateBLEVals(vector<float> newVals);
    void update();
protected:
    maxiOsc osc;
    float ringMod;
    float sigAvg1, sigAvg2;
private:
    
};

#endif /* defined(__sonicTag2NB__sceneFXPlay1__) */
