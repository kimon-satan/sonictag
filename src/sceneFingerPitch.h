//
//  sceneFingerPitch.h
//  sonicTag2
//
//  Created by Chris Kiefer on 28/06/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#ifndef sonicTag2_sceneFingerPitch_h
#define sonicTag2_sceneFingerPitch_h


#include "sceneFingerStretch.h"

class sceneFingerPitch : public sceneFingerStretch {
public:
    string getTitle() {return "Pitch Stretch";}    
    audioProcessor* getAudioProcessor() {return new passThroughAudioProcessor();};    
    void handleInterfaceEvent(int id, int eventTypeId, EAVIGUI::InterfaceObject *object);
    string getSubTitle() {return "Drag your finger in a circle to change the pitch.";};
    void doBarChangeEvent();
};

#endif
