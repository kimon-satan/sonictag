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
#include "EAVIGUI.InterfaceManager.h"
#include "DRSGrains.h"
#include "waveform.h"

#include "BLEScanner.h"
#include "nbStream.h"

#include "supervisorMenu.h"

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
    bool lockNavigation, tempLockNavigation;
        
    vector<vector<baseScene*> > grid;
    int gridX, gridY;
    bool isASceneStartedYet;
    
    void updateScene(int sceneX, int sceneY);
    stringstream autoSaveName;
    
    //GUI
    enum GUIIDS {
        LEFTARROW, RIGHTARROW, UPARROW, DOWNARROW, NAVMENU, BACKZOOM, WAV,
        CORNERBUTTON1, CORNERBUTTON2, CORNERBUTTON3, CORNERBUTTON4
    };
	void handleInterfaceEvent(int id, int eventTypeId, EAVIGUI::InterfaceObject *object);
    EAVIGUI::ImageButton *navLeftArrow, *navRightArrow, *navUpArrow, *navDownArrow;
    EAVIGUI::ImageButton *cornerButton1, *cornerButton2, *cornerButton3, *cornerButton4;
    void setNavVisibility();
    
    EAIT::ChangeTriggerI canProgressChange;
    
    bool sceneIsUpdating;
    
    ofVideoPlayer introVid;
    
    enum appPhases {
        LOADING,
        REMIX
    } appPhase;
    
    int backgroundOrientation;
    
    supervisorMenu svMenu;
    
    
    //BLE
    void onValueUpdate();
    BLEScanner *scanner;
    static const int NUMNBSTREAMS = 16;
    vector<float> bleVals;
    nbStream nbStreams[NUMNBSTREAMS];
    EAIT::MovingAverage<float> bleMA[NUMNBSTREAMS];
    float bleMeterSize;
    int bleFrameCount;
    float vals[NUMNBSTREAMS], lastVals[NUMNBSTREAMS];
    maxiDCBlocker dcblock[NUMNBSTREAMS];
    maxiDCBlocker dcMasterBlocker;
    float dcBlockTotal;
    
    bool useNoiseBear;

    
};


