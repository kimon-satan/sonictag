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
#include <sstream>
#include "MIRListener.h"

class sharedDataContainer {
public:
    sharedDataContainer() {
        colours.resize(4);
        randomiseColours();
    }

    vector<short> recordBuffer;
    maxiSample buffer;
    std::vector<ofColor> colours;
    void randomiseColours() {
        for(int i=0; i < colours.size(); i++) {
            colours[i].set(floor(ofRandom(255)),floor(ofRandom(255)),floor(ofRandom(255)));
        }
    }
    
    MIRListener mir;
    
    ~sharedDataContainer() {
    }
    
};


#endif
