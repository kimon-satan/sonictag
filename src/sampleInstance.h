//
//  sampleInstance.h
//  DRSApp
//
//  Created by Chris Kiefer on 27/07/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#ifndef DRSApp_sampleInstance_h
#define DRSApp_sampleInstance_h

#include "ofxMaxim.h"
#include "audioProcessor.h"


class MIRListener : public audioProcessor {
public:
    MIRListener() {
        env.setAttack(10);
        env.setRelease(10);
    }
    
    float play(float input){
        env.play(input);
        return 0;
    };
    
    maxiEnvelopeFollower env;
};

class sampleInstance {
public:
    maxiSample sample;
    int gridX, gridY;
    ofImage icon;
    int slot;
    
    MIRListener mir;
    
    sampleInstance(maxiSample &source) {
        sample = source; //copy sample data
    }

    vector<audioProcessor*> audioFlow;
    
    ~sampleInstance() {
        for(int i=0; i < audioFlow.size(); i++) {
            delete audioFlow[i];
        }
    }

};

#endif
