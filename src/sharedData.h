//
//  sharedData.h
//  sonicTag2
//
//  Created by Chris Kiefer on 27/06/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#ifndef sonicTag2_sharedData_h
#define sonicTag2_sharedData_h

#include "ofxMaxim.h"
#include "assets.h"
#include <sstream>
#include "sampleInstance.h"
#include "dimensions.h"

class sharedDataContainer {
public:
    sharedDataContainer() {
        colours.resize(4);
        randomiseColours();
        audioLoaded = false;
        currSampleInstance = NULL;
    }
    vector<short> recordBuffer;
    maxiSample buffer;
    std::vector<ofColor> colours;
    void randomiseColours() {
        for(int i=0; i < colours.size(); i++) {
            colours[i].set(floor(ofRandom(255)),floor(ofRandom(255)),floor(ofRandom(255)));
        }
    }
    
    //assets
    song *currSong;
    vector<maxiSample> audioTracks;
    bool audioLoaded;
    
    vector<sampleInstance*> sampleInstances;
    sampleInstance *currSampleInstance;

    ~sharedDataContainer() {
        for(int i=0; i < sampleInstances.size(); i++) {
            delete sampleInstances[i];
        }
    }
    
    ofImage backdrop;
    int barLength; // in samples
    
    DRSDATA::dimensions currentDimension;
};


#endif
