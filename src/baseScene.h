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


#ifndef sonicTag2_baseScene_h
#define sonicTag2_baseScene_h

#include "ofMain.h"
#include "sharedData.h"
#ifdef TARGET_OF_IPHONE
    #include "ofxiPhone.h"
#endif

#include "log.h"
#include "EAVIGUI.interfaceManager.h"
#include "EAIT.h"
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
    void onBarStart();
    virtual void doBarChangeEvent();
    EAIT::Flag respondToBarChange;
    int getSceneID(){return sceneID;}
    bool enabled;
    virtual bool canProgress();
    int currentOrientation, prevoiusOrientation;
    virtual void updateBLEVals(vector<float> newVals, float sigAvg) {bleVals = newVals; nbConnected = true;}
    maxiDyn compressor;
    virtual void updateTitle();
    
protected:
    sharedDataContainer *sharedData;
    EAVIGUI::InterfaceObjectGroup interface;
    static EAIT::Counter<int> objectIDCounter;
    static EAIT::Counter<int> sceneIDCounter;
    int sceneID;
    vector<float> bleVals;
    bool nbConnected;  //noise bear connected?
    EAVIGUI::Label *title;

};

#endif
