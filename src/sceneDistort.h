//
//  sceneDistort.h
//  DRSApp
//
//  Created by Chris Kiefer on 01/08/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#ifndef DRSApp_sceneDistort_h
#define DRSApp_sceneDistort_h

#include "sceneGain.h"

class audioProcessorDistort : public audioProcessor {
public:
    audioProcessorDistort() {level=1;}
    inline float play(float input) {return dist.fastAtanDist(input, level);}
//    float play(float input) {return input;}
    float level;
    maxiDistortion dist;
};


class sceneDistort : public sceneGain {
public:
    string getTitle() {return string("Distortion");}
    audioProcessor* getAudioProcessor() {return new audioProcessorDistort();};  
    void setAudioProcessor(audioProcessor* currProcessor);
    
    void handleInterfaceEvent(int id, int eventTypeId, EAVIGUI::InterfaceObject *object);
    string getSubTitle() {return "Drag the circular bar to distort the sound.";};
    
protected:
    
};

#endif
