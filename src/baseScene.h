//
//  baseScene.h
//  sonicTag2
//
//  Created by Chris Kiefer on 27/06/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#ifndef sonicTag2_baseScene_h
#define sonicTag2_baseScene_h

#include "ofMain.h"
#include "sharedData.h"
#ifdef TARGET_OF_IPHONE
    #include "ofxiPhone.h"
#endif

#include "log.h"
#include "interfaceManager.h"
#include "EAIT.h"
#include "audioProcessor.h"
#include "ofxMaxim.h"


class baseScene : public EAVIGUI::InterfaceListener {
public:
    virtual void setup(sharedDataContainer *data);
    virtual void update();
    virtual void draw();
    virtual void audioRequested( float * output, int bufferSize, int nChannels );
    virtual void audioIn( float * input, int bufferSize, int nChannels ); 
    virtual void touchDown(ofTouchEventArgs &touch);
	virtual void touchMoved(ofTouchEventArgs &touch);
	virtual void touchUp(ofTouchEventArgs &touch);
	virtual void touchDoubleTap(ofTouchEventArgs &touch);
	virtual void touchCancelled(ofTouchEventArgs &touch);
    virtual void beginScene();
    virtual void endScene();
    virtual string getTitle();
    virtual string getSubTitle();
    virtual void handleInterfaceEvent(int id, int eventTypeId, EAVIGUI::InterfaceObject *object);
    virtual audioProcessor* getAudioProcessor();
    virtual void setAudioProcessor(audioProcessor* currProcessor) {currAudioProcessor = currProcessor;};
    void onBarStart();
    virtual void doBarChangeEvent();
    EAIT::Flag respondToBarChange;
    int getSceneID(){return sceneID;}
    bool enabled;
    virtual bool canProgress();
    int currentOrientation, prevoiusOrientation;
    virtual void updateBLEVals(vector<float> newVals, float sigAvg) {bleVals = newVals; nbConnected = true;}
    maxiDyn compressor;
    
protected:
    audioProcessor* currAudioProcessor;
    sharedDataContainer *sharedData;
    EAVIGUI::InterfaceObjectGroup interface;
    static EAIT::Counter<int> objectIDCounter;
    static EAIT::Counter<int> sceneIDCounter;
    int sceneID;
    vector<float> bleVals;
    bool nbConnected;  //noise bear connected?

};

#endif
