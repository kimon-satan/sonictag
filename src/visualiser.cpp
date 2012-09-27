//
//  visualiser.cpp
//  sonicTag2
//
//  Created by Chris Kiefer on 05/07/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#include <iostream>
#include "visualiser.h"

void visualiser::setup(sharedDataContainer *data) {
    fft.setup(1024, 512, 256);
    mfcc.setup(512, 42, 14, 20, 20000, 44100);
    mfccCoeffs.resize(14);
    radius = ofGetWidth()/3.0;
    cx = ofGetWidth()/2.0;
    cy = ofGetHeight()/2.0;
    sharedData = data;
}


void visualiser::analyseAudio(float * output, int bufferSize, int nChannels) {
    for(int i=0; i < bufferSize * nChannels; i++) {
        if (fft.process(output[i])) {
            mfcc.mfcc(fft.magnitudes, &mfccCoeffs[0]);
            for (int i=0; i < 4; i++) {
                val[i]=interp[i].lopass(fabs(mfccCoeffs[i+1]),0.2*fabs(mfccCoeffs[i+1]));
            }            
        }
    }    
}

void visualiser::draw() {
    float unit = radius / mfccCoeffs.size();
    for(int i=0; i < 4; i++) {
        ofSetColor(sharedData->colours[i].r, sharedData->colours[i].g, sharedData->colours[i].b, val[i] * 255);
//        ofSetColor(0,0,0, val[i] * 255.0);
        ofCircle(cx, cy, (unit * (i*4)) + (val[i]*400));
        //        stringstream tmp;
        //        tmp << mfccCoeffs[i];
        //        ofDrawBitmapString(tmp.str(), 10, 100 + (i * 50));
    }
}

