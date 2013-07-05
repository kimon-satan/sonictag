//
//  sceneHPFilterPlay.cpp
//  sonicTag2NB
//
//  Created by Chris on 13/03/2013.
//
//

#include "sceneHPFilterPlay.h"

void sceneHPFilterPlay::audioRequested( float * output, int bufferSize, int nChannels ) {
    filt.setCutoff(freq);
    filt.setResonance(res);
    for(int i=0; i<bufferSize; i++) {
        output[i] = sharedData->buffer.playLoop(sharedData->loopStart, sharedData->loopEnd) * 0.8;
        output[i] = filt.play(output[i], 0.0, 1.0, 0.0, 0.0);
        if (output[i] > 0.99) output[i] = 0.99;
        else if (output[i] <-0.99) output[i] = -0.99;
    }
}
