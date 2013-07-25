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

