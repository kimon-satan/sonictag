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
        ofCircle(cx, cy, (unit * (i*4)) + (val[i]*400));
    }
}

