/*
 This file is part of 'Sonic Tag'.
 This software is released under a simplified BSD license, modified for non-commercial use only.
 
 Copyright (c) 2013, M.Grierson, Embodied AudioVisual Interaction Group, Goldsmiths, University of London
 
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are
 met:
 
 * Redistributions of source code must retain the above copyright
 notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above
 copyright notice, this list of conditions and the following disclaimer
 in the documentation and/or other materials provided with the
 distribution.
 * Any redistribution, use, or modification is done solely for
 personal benefit and not for any commercial purpose or for monetary
 gain
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
 For further information:
 http://eavi.goldsmithsdigital.com/sound-image-and-brain/
 http://eavi.goldsmithsdigital.com/sonic-tag/
 
 */

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


