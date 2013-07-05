//
//  sceneFXPlay1.cpp
//  sonicTag2NB
//
//  Created by Chris on 13/03/2013.
//
//

#include "sceneFXPlay1.h"

//void sceneFXPlay1::updateBLEVals(vector<float> newVals) {
//    baseScene::updateBLEVals(newVals);
//    float avg1 = 0;
//    for(int i=0; i < bleVals.size() / 2; i++) {
//        avg1 += bleVals[i];
//    }
//    sigAvg1 = avg1 / ((float) bleVals.size() / 2);
//    float avg2 = 0;
//    for(int i=bleVals.size() / 2; i < bleVals.size(); i++) {
//        avg2 += bleVals[i];
//    }
//    sigAvg2 = avg2 / ((float) bleVals.size() / 2);
//}

void sceneFXPlay1::update() {
    sceneFilterPlay::update();
//    cout << surface->getVelocity() << endl;
    ringMod = maxiMap::linexp(surface->getAngle(), 0.01, PI * 2.0, 40, 10000);
//    res = maxiMap::linexp(surface->getVelocity(), 0.01, 0.2, 0.1, 1.0);
}


void sceneFXPlay1::audioRequested( float * output, int bufferSize, int nChannels ) {
    memset(output, 0, sizeof(float) * bufferSize * nChannels);
    for(int i=0; i<bufferSize; i++) {
        output[i] = sharedData->buffer.playLoop(sharedData->loopStart, sharedData->loopEnd) * 0.9;
        output[i] = output[i] * osc.sinebuf(ringMod);
        output[i] = filt.play(output[i], 1.0, 0, 0, 0);
        if (output[i] > 0.99) output[i] = 0.99;
        else if (output[i] <-0.99) output[i] = -0.99;
    }
}

