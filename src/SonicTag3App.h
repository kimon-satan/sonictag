#pragma once

#include "ofMain.h"
#ifdef TARGET_OF_IPHONE
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#endif

#include "ofxMaxim.h"
//#include "ofxOsc.h"
#include "baseScene.h"
#include <tr1/memory> 
#include "sharedData.h"
#include "InterfaceManager.h"
#include "DRSGrains.h"
#include "waveform.h"

//#define LATCHMODE

class SonicTag3App : EAVIGUI::InterfaceListener {
	
public:
	void setup();
	void update();
	void draw();
	void exit();
	
	void touchDown(ofTouchEventArgs &touch);
	void touchMoved(ofTouchEventArgs &touch);
	void touchUp(ofTouchEventArgs &touch);
	void touchDoubleTap(ofTouchEventArgs &touch);
	void touchCancelled(ofTouchEventArgs &touch);

	void lostFocus();
	void gotFocus();
	void gotMemoryWarning();
	void deviceOrientationChanged(int newOrientation);
    
    void audioRequested( float * output, int bufferSize, int nChannels );
    void audioIn( float * input, int bufferSize, int nChannels );
    
    bool isRecording;
    maxiFilter lpf;
    unsigned long long sampleCounter;
    
    void gotMessage(ofMessage& msg);
    
//    ofxOscSender oscOut;
    
    bool isRecordingOutput;
    vector<short> wav;
    
    
    ofTrueTypeFont navFont, navFontSmall;
    float navButtonSize;
//    bool navTrigLeft, navTrigRight, navTrigUp, navTrigDown, navLeftEnabled, navRightEnabled, navUpEnabled, navDownEnabled;
    sharedDataContainer sharedData;
        
    vector<vector<baseScene*> > grid;
    int gridX, gridY;
    bool isASceneStartedYet;
    
    void updateScene(int sceneX, int sceneY);
    stringstream autoSaveName;
    
    //GUI
    enum GUIIDS {
        LEFTARROW, RIGHTARROW, UPARROW, DOWNARROW, NAVMENU, BACKZOOM, WAV
    };
	void handleInterfaceEvent(int id, int eventTypeId, EAVIGUI::InterfaceObject *object);
    EAVIGUI::ImageButton *navLeftArrow, *navRightArrow, *navUpArrow, *navDownArrow;
    void setNavVisibility();
    
    EAIT::ChangeTriggerI canProgressChange;
    
    bool sceneIsUpdating;
    
    ofVideoPlayer introVid;
    
    enum appPhases {
        LOADING,
        REMIX
    } appPhase;
    
    int backgroundOrientation;
    
    
        
};


