//
//  sceneFingerStretch.h
//  sonicTag2
//
//  Created by Chris Kiefer on 28/06/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#ifndef sonicTag2_sceneFingerStretch_h
#define sonicTag2_sceneFingerStretch_h

#include "scenePlay.h"
#include "RadialScratchSurface.h"
#include "DRSGrains.h"

#ifdef TARGET_OF_IPHONE
typedef DRSmaxiPitchStretch<float, DRShannWinFunctor<float> > grainPlayerType;
#else
typedef DRSmaxiPitchStretch<double, DRShannWinFunctor<double> > grainPlayerType;
#endif

class audioProcessorTimeStretch : public audioProcessor {
public:
    audioProcessorTimeStretch() {stretch = 1.0; pitch = 1.0; pitchStretch = NULL;}
    ~audioProcessorTimeStretch() {if (pitchStretch) delete pitchStretch;}
    void setSample(maxiSample *samp, int numBars) {
        audioProcessor::setSample(samp, numBars);
//        pitchStretch = new maxiPitchStretch<hannWinFunctor>(samp);        
        pitchStretch = new grainPlayerType(samp);        
        barDivisor = 1.0 / (double) numBars;
    };
    float play(float input) {return pitchStretch->play(pitch, stretch, 0.05, 2);}
    grainPlayerType *pitchStretch;  
    float stretch;
    float pitch;
    void resync() {
        double currPos = pitchStretch->getNormalisedPosition();
        float newPosition = currPos - fmod((double)currPos, (double)barDivisor);
        pitchStretch->setPosition(newPosition);
    }
protected:
    double barDivisor;
};


class sceneFingerStretch : public scenePlay {
public:
    void setup(sharedDataContainer *data);
    string getTitle() {return "Time Stretch";}
    audioProcessor* getAudioProcessor() {return new audioProcessorTimeStretch();};
    void handleInterfaceEvent(int id, int eventTypeId, EAVIGUI::InterfaceObject *object);
    EAIT::MovingAverageF velMA;
    void doBarChangeEvent(); 
    void beginScene();
    void endScene();
    string getSubTitle() {return "Drag your finger in a circle to change the speed.";};    
protected:
    EAVIGUI::RadialScratchSurface *surface;
};

#endif
