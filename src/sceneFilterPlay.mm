//
//  sceneFilterPlay.cpp
//  sonicTag2NB
//
//  Created by Chris on 12/03/2013.
//
//

#include "sceneFilterPlay.h"
#include <iostream>
#include <sstream>
#include "audioCatalogue.h"

void sceneFilterPlay::setup(sharedDataContainer *data) {
    surface = new EAVIGUI::RadialScratchSurface(this, objectIDCounter.next(), 0, 0, ofGetWidth(), ofGetWidth());
    surface->setRelativePositioning(0.5, -ofGetWidth()/2.0, 0.5, -ofGetWidth()/2.0);
    surface->setAnchorPoint(0.5, 0.5);
    interface.push_back(surface);

    baseScene::setup(data);
    
    freq = 200;
    res = 0.5;
}

//void sceneFilterPlay::updateBLEVals(vector<float> newVals) {
//    baseScene::updateBLEVals(newVals);
//        float avg = 0;
//        for(int i=0; i < bleVals.size(); i++) {
//            avg += bleVals[i];
//        }
//        sigAvg = avg / (float) bleVals.size();
//}


void sceneFilterPlay::update() {
    baseScene::update();
    freq = maxiMap::linexp(surface->getAngle(), 0.01, PI * 2.0, 200, 10000);
    res = maxiMap::linlin(surface->getDistToCenter(), 0, 400, 0, 1.0);
    cout << surface->getDistToCenter() << ", " << freq << ", " << res << endl;
}


void sceneFilterPlay::audioRequested( float * output, int bufferSize, int nChannels ) {
    for(int i=0; i<bufferSize; i++) {
        output[i] = sharedData->buffer.play();
        output[i] = filt.lores(output[i], freq, res);
    }
}


void sceneFilterPlay::beginScene() {
    baseScene::beginScene();
}

void sceneFilterPlay::endScene() {
    baseScene::endScene();
}

