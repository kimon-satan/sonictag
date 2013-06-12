//
//  sceneHPFilterPlay.cpp
//  sonicTag2NB
//
//  Created by Chris on 13/03/2013.
//
//

#include "sceneHPFilterPlay.h"

void sceneHPFilterPlay::audioRequested( float * output, int bufferSize, int nChannels ) {
    memset(output, 0, sizeof(float) * bufferSize * nChannels);
    for(int i=0; i<bufferSize; i++) {
        output[i] = sharedData->buffer.play() * 0.5;
        output[i] = filt.hires(output[i], freq, res);
    }
}
