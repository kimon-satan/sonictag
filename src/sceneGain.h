//
//  sceneGain.h
//  DRSApp
//
//  Created by Chris Kiefer on 31/07/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#ifndef DRSApp_sceneGain_h
#define DRSApp_sceneGain_h

#include "scenePlay.h"
#include "circularDial.h"

class audioProcessorGain : public audioProcessor {
public:
    audioProcessorGain() {amp=1.0;}
    float play(float input) {return input * amp;}
    float amp;
};


class sceneGain : public scenePlay {
public:
    void setup(sharedDataContainer *data);
    string getTitle() {return string("Volume");}
    audioProcessor* getAudioProcessor() {return new audioProcessorGain();};  
    void setAudioProcessor(audioProcessor* currProcessor);

    void handleInterfaceEvent(int id, int eventTypeId, EAVIGUI::InterfaceObject *object);
    string getSubTitle() {return "Drag the circular bar to change the volume.";};

protected:
    EAVIGUI::CircularDial *dial;
    void processTouch(ofTouchEventArgs &touch);
    float angle;
    
};

#endif
