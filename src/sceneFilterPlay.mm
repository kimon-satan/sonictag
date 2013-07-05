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
    surface = new EAVIGUI::RadialScratchSurface(this, objectIDCounter.next(), 0, 0, ofGetHeight(), ofGetHeight());
    surface->setRelativePositioning(0.5, -surface->getScaledWidth()/2.0, 0.5, -surface->getScaledHeight()/2.0);
    surface->setAnchorPoint(0.5, 0.5);
    interface.push_back(surface);

    baseScene::setup(data);
    
    freq = 2000;
    res = 0.1;
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
    freq = maxiMap::linexp(surface->getAngle(), 0.01, PI * 2.0, 200, 15000);
    res = maxiMap::linlin(surface->getDistToCenter(), 0, 400, 0, 3.0);
    cout << surface->getDistToCenter() << ", " << freq << ", " << res << endl;
}


void sceneFilterPlay::audioRequested( float * output, int bufferSize, int nChannels ) {
    filt.setCutoff(freq);
    filt.setResonance(res);
    for(int i=0; i<bufferSize; i++) {
        output[i] = sharedData->buffer.play();
        output[i] = filt.play(output[i], 1.0, 0.0, 0.0, 0.0);
    }
}


void sceneFilterPlay::beginScene() {
    baseScene::beginScene();
}

void sceneFilterPlay::endScene() {
    baseScene::endScene();
}

void sceneFilterPlay::handleInterfaceEvent(int id, int eventTypeId, EAVIGUI::InterfaceObject *object) {
    baseScene::handleInterfaceEvent(id, eventTypeId, object);
}


