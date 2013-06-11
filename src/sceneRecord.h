//
//  sceneRecord.h
//  sonicTag2
//
//  Created by Chris Kiefer on 27/06/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#ifndef sonicTag2_sceneRecord_h
#define sonicTag2_sceneRecord_h

#include "baseScene.h"
#include "ofxMaxim.h"
#include "ofMain.h"
#include "EAIT.h"

class sceneRecord : public baseScene {
public:
    void setup(sharedDataContainer *data);
    void update();
    void draw();
    void audioRequested( float * output, int bufferSize, int nChannels );
    void audioIn( float * input, int bufferSize, int nChannels );  
    void touchDown(ofTouchEventArgs &touch);
	void touchUp(ofTouchEventArgs &touch);
    float markerAngle, radius, cx, cy;
    void beginScene();    
    void endScene();    
    string getTitle() {return string("Record").append(armedRecord ? " (trig)" : "");}
    bool armedRecord;
    void handleInterfaceEvent(int id, int eventTypeId, EAVIGUI::InterfaceObject *object);
    void updateBLEVals(vector<float> newVals, float sigAvg);

private:
    void initRecording();
    bool recording;
    bool recordingArmed;
    maxiFilter interpol;
    double ampVal, ampValAvg;
    EAIT::MovingRMSF rmsMA;
    int recordCounter;
    void initialiseRecording();
    void finaliseRecording();
};

#endif
