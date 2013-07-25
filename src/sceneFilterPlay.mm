/*
 This file is part of 'Sonic Tag'.
 This software is released under a simplified BSD license, modified for non-commercial use only.
 
 Copyright (c) 2013, M.Grierson, Embodied AudioVisual Interaction Group, Goldsmiths, University of London
 
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are
 met:
 
 * Redistributions of source code must retain the above copyright
 notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above
 copyright notice, this list of conditions and the following disclaimer
 in the documentation and/or other materials provided with the
 distribution.
 * Any redistribution, use, or modification is done solely for
 personal benefit and not for any commercial purpose or for monetary
 gain
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
 For further information:
 http://eavi.goldsmithsdigital.com/sound-image-and-brain/
 http://eavi.goldsmithsdigital.com/sonic-tag/
 
 */


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


