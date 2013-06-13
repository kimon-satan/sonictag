//
//  sceneHPFilterPlay.cpp
//  sonicTag2NB
//
//  Created by Chris on 13/03/2013.
//
//

#include "sceneHPFilterPlay.h"

void sceneHPFilterPlay::audioRequested( float * output, int bufferSize, int nChannels ) {
    for(int i=0; i<bufferSize; i++) {
        output[i] = sharedData->buffer.play() * 0.9;
        output[i] = filt.hires(output[i], freq, res);
    }
}
