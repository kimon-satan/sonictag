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


#include "sceneFXPlay2.h"

void sceneFXPlay2::update(){
    sigAvg1 = surface->getAngle() / (2.0 * PI);
    sigAvg2 = surface->getDistToCenter() / (float)ofGetWidth();
    sigAvg3 = surface->getDistToCenter() / (float)ofGetWidth();
    sigAvg3 = (sigAvg2 + sigAvg3) / 2.0;
    cout << sigAvg1 << ", " << sigAvg2 << ", " << sigAvg3 << endl;
}

void sceneFXPlay2::audioRequested( float * output, int bufferSize, int nChannels ) {
    memset(output, 0, sizeof(float) * bufferSize * nChannels);
    for(int i=0; i<bufferSize; i++) {
        output[i] = sharedData->buffer.play();
        output[i] = flange.flange(output[i], 800, 0.6 + (sigAvg1 * 0.4), sigAvg2 * 90.0, min(1.0f, sigAvg3 * 10.0f)) * 0.9;
        if (output[i] > 0.99) output[i] = 0.99;
        else if (output[i] <-0.99) output[i] = -0.99;
    }
}
