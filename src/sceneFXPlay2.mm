//
//  sceneFXPlay2.cpp
//  sonicTag2NB
//
//  Created by Chris on 13/03/2013.
//
//

#include "sceneFXPlay2.h"

//void sceneFXPlay2::updateBLEVals(vector<float> newVals) {
//    baseScene::updateBLEVals(newVals);
//    float avg1 = 0;
//    for(int i=0; i < bleVals.size() / 3; i++) {
//        avg1 += bleVals[i];
//    }
//    sigAvg1 = avg1 / ((float) bleVals.size() / 3);
//    float avg2 = 0;
//    for(int i=bleVals.size() / 3; i < bleVals.size() / 3 * 2; i++) {
//        avg2 += bleVals[i];
//    }
//    sigAvg2 = avg2 / ((float) bleVals.size() / 3);
//    float avg3 = 0;
//    for(int i=bleVals.size() / 3 * 2; i < bleVals.size(); i++) {
//        avg3 += bleVals[i];
//    }
//    sigAvg3 = avg3 / ((float) bleVals.size() / 3);
//}


void sceneFXPlay2::update(){
    sigAvg1 = surface->getAngle() / (2.0 * PI);
    sigAvg2 = surface->getDistToCenter() / 400.0;
    sigAvg3 = surface->getDistToCenter() / 400.0;
    sigAvg3 = (sigAvg2 + sigAvg3) / 2.0;
}

void sceneFXPlay2::audioRequested( float * output, int bufferSize, int nChannels ) {
    memset(output, 0, sizeof(float) * bufferSize * nChannels);
    for(int i=0; i<bufferSize; i++) {
        output[i] = sharedData->buffer.play();
        output[i] = flange.flange(output[i], 800, sigAvg1, sigAvg2 * 30, min(1.0f, sigAvg3 * 2)) * 0.5;
    }
}
