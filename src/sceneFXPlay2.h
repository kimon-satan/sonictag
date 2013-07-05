//
//  sceneFXPlay2.h
//  sonicTag2NB
//
//  Created by Chris on 13/03/2013.
//
//

#ifndef __sonicTag2NB__sceneFXPlay2__
#define __sonicTag2NB__sceneFXPlay2__

#include <iostream>
#include "sceneFilterPlay.h"

using namespace std;

class sceneFXPlay2 : public sceneFilterPlay {
public:
    void audioRequested( float * output, int bufferSize, int nChannels );
    string getTitle() {return string("Flanger");}
    void update();
//    void updateBLEVals(vector<float> newVals);
protected:
    maxiFlanger flange;
    float sigAvg1, sigAvg2, sigAvg3;
private:
    
};

#endif /* defined(__sonicTag2NB__sceneFXPlay2__) */
