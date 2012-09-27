//
//  visualiser.h
//  sonicTag2
//
//  Created by Chris Kiefer on 05/07/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#ifndef sonicTag2_visualiser_h
#define sonicTag2_visualiser_h

#include "ofMain.h"
#include "ofxMaxim.h"
#include "sharedData.h"

class visualiser {
public:
    void setup(sharedDataContainer *sharedData);
    void analyseAudio(float * output, int bufferSize, int nChannels);
    void draw();

    maxiFFT fft;
    maxiMFCC mfcc;
    vector<double> mfccCoeffs;
    
    float radius, cx, cy, val[4];
    
    ofxMaxiFilter interp[4];
    sharedDataContainer *sharedData;
    
    
};

#endif
