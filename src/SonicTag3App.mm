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

#include "SonicTag3App.h"
#include <sstream>
#include "sharedData.h"
#include "sceneRecord.h"
#include "scenePlay.h"
#include "sceneLoopRecord.h"
#include "sceneFingerPlay.h"
#include "sceneFingerStretch.h"
#include "sceneFingerPitch.h"
#include "sceneFingerPitchStretch.h"
#include "sceneAccelStretch.h"
#include "sceneAccelPitch.h"
#include "sceneAccelPitchStretch.h"
#include "audioCatalogue.h"
#include "log.h"
#include "sceneFilterPlay.h"
#include "sceneHPFilterPlay.h"
#include "sceneFXPlay1.h"
#include "sceneFXPlay2.h"
#include "sceneLoop.h"

const int trigTime = 50;

static void notificationHandler(CFNotificationCenterRef center, void *observer, CFStringRef name, const void *object, CFDictionaryRef userInfo) {
//    cout << "Nofitifcation received\n";
    (static_cast<SonicTag3App *>(observer))->onValueUpdate();
}

NSString *USENOISEBEARKEY = @"noisebear_enabled";

//--------------------------------------------------------------
void SonicTag3App::setup(){	
    
    ofRegisterGetMessages(this);
    appPhase = REMIX;
    sampleCounter=0;
    ofSetLogLevel(OF_LOG_WARNING);
    
    ofSetFrameRate(60);
    //user details for noisebear
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults]; 
    useNoiseBear = false;
    if ([defaults boolForKey:USENOISEBEARKEY] == YES) {
        useNoiseBear = true;
        cout << "Noisebear enabled\n";
    }
    
    
    CFNotificationCenterAddObserver
    (
     CFNotificationCenterGetLocalCenter(),
     this,
     &notificationHandler,
     CFSTR("notify"),
     NULL,
     CFNotificationSuspensionBehaviorDeliverImmediately
    );

    //preallocate some silence
    sharedData.buffer.setLength(maxiSettings::sampleRate * 2);

    sceneIsUpdating = false;
	
    log::init(ofxiPhoneGetDocumentsDirectory());
    
    ofTrueTypeFont::setGlobalDpi(72);

    //GUI
    navFont.loadFont("LARABIEF.TTF", 80);
    navFontSmall.loadFont("mono.ttf", 25);
    lockNavigation = false;
    
    EAVIGUI::InterfaceManager::deviceScaleMod = 1.0;
    UIDevice* thisDevice = [UIDevice currentDevice];
    if(thisDevice.userInterfaceIdiom == UIUserInterfaceIdiomPad)
    {
        EAVIGUI::InterfaceManager::deviceScaleMod = 1.0;
    }
    else
    {
        EAVIGUI::InterfaceManager::deviceScaleMod = 0.41;
    }    
    
    EAVIGUI::InterfaceManager::addFont("titles", "Kannada Sangam MN.ttf", 40);
    EAVIGUI::InterfaceManager::addFont("kannada_small", "Kannada Sangam MN.ttf", 24);
    EAVIGUI::InterfaceManager::addFont("subtitles", "mono.ttf", 20);
    EAVIGUI::InterfaceManager::addFont("small", "mono.ttf", 25);
    EAVIGUI::InterfaceManager::addFont("big", "ka1.ttf", 50);
    EAVIGUI::InterfaceManager::addFont("bigger", "ka1.ttf", 60);
    EAVIGUI::InterfaceManager::addFont("c64Rounded", "Commodore Rounded v1.2.ttf", 20);

    
    audioCatalogue::scan();
    audioCatalogue::deleteOldRecordings();
    
    isRecording = false;
    isRecordingOutput = false;
    
    int gridWidth=5;
    int gridHeight = 5;
    grid.resize(gridWidth);
    for(int i=0; i < grid.size(); i++) {
        grid[i].resize(gridHeight, NULL);
    }
    gridX = 0;
    gridY = 0;    
    isASceneStartedYet = false;
    

    grid[0][0] = new sceneRecord();
    grid[1][0] = new scenePlay();
    grid[2][0] = new sceneFingerStretch();
    grid[3][0] = new sceneFingerPitch();
    grid[4][0] = new sceneFingerPitchStretch();
    
    grid[0][1] = new sceneLoopRecord();
    grid[1][1] = new scenePlay();
    grid[2][1] = new sceneAccelStretch();
    grid[3][1] = new sceneAccelPitch();
    grid[4][1] = new sceneAccelPitchStretch();

    grid[0][2] = NULL;
    grid[1][2] = new sceneLoop();
    grid[2][2] = new sceneAccelStretch();
    grid[3][2] = new sceneAccelPitch();
    grid[4][2] = new sceneAccelPitchStretch();

    grid[0][3] = NULL;
    grid[1][3] = NULL;
    grid[2][3] = new sceneAccelStretch();
    grid[3][3] = new sceneAccelPitch();
    grid[4][3] = new sceneAccelPitchStretch();

    grid[0][4] = NULL;
    grid[1][4] = NULL;
    grid[2][4] = new sceneHPFilterPlay();
    grid[3][4] = new sceneFXPlay1();
    grid[4][4] = new sceneFXPlay2();

    for(int i=0; i < grid.size(); i++) {
        for(int j=0; j < grid[i].size(); j++) {
            if (grid[i][j] != NULL) {
                grid[i][j]->setup(&sharedData);
                grid[i][j]->enabled = true;
            }
        }
    }
    
    
    navButtonSize = 90;
    navLeftArrow = (new EAVIGUI::ImageButton(this, LEFTARROW, 0, 0, "arrowleftS.png", "arrowleftS.png"));
    navLeftArrow->setRelativePositioning(0, 0, 0.5, -(navLeftArrow->getScaledHeight() / 2.0));
    navLeftArrow->setAnchorPoint(0, 0);
   // navLeftArrow->pulsate = true;
    navLeftArrow->fadeTime = 100;
    EAVIGUI::InterfaceManager::addObject(navLeftArrow);
    
    navRightArrow = new EAVIGUI::ImageButton(this, RIGHTARROW, 0, 0, "arrowrightS.png", "arrowrightS.png");
    navRightArrow->setRelativePositioning(1.0, -navRightArrow->getScaledWidth(), 0.5, -(navRightArrow->getScaledHeight() / 2.0));
    navRightArrow->setAnchorPoint(0, 0);
  //  navRightArrow->pulsate = true;
    navRightArrow->fadeTime = 100;
    EAVIGUI::InterfaceManager::addObject(navRightArrow);
    
    navUpArrow = new EAVIGUI::ImageButton(this, UPARROW, 0, 0, "arrowupS.png", "arrowupS.png");
    navUpArrow->setRelativePositioning(0.5, -(navUpArrow->getScaledWidth()/2.0), 0, 0);
    navUpArrow->setAnchorPoint(0, 0);
  //  navUpArrow->pulsate = true;
    navUpArrow->fadeTime = 100;
    EAVIGUI::InterfaceManager::addObject(navUpArrow);
    
    navDownArrow = new EAVIGUI::ImageButton(this, DOWNARROW, 0, 0, "arrowdownS.png", "arrowdownS.png");
    navDownArrow->setRelativePositioning(0.5, -(navDownArrow->getScaledWidth() / 2.0), 1.0, -navDownArrow->getScaledHeight());
    navDownArrow->setAnchorPoint(0, 0);
  //  navDownArrow->pulsate = true;
    navDownArrow->fadeTime = 100;
    EAVIGUI::InterfaceManager::addObject(navDownArrow);

    cornerButton1 = new EAVIGUI::ImageButton(this, CORNERBUTTON1, 0, 0, "cornerButton.png", "cornerButtonT.png");
    cornerButton1->setRelativePositioning(1.0, -cornerButton1->getScaledWidth(), 1.0 , -cornerButton1->getScaledHeight());
    cornerButton1->setColor(ofColor(255,255,255,170));
    cornerButton1->setCanTouchTranparency(true);
    EAVIGUI::InterfaceManager::addObject(cornerButton1);
    cornerButton1->setVisible(true);
    cornerButton2 = new EAVIGUI::ImageButton(this, CORNERBUTTON2, 0, 0, "cornerButton.png", "cornerButtonT.png");
    cornerButton2->setRelativePositioning(0.0, 0.0, 1.0 , -cornerButton2->getScaledHeight());
    cornerButton2->setColor(ofColor(255,255,255,170));
    cornerButton2->setCanTouchTranparency(true);
    EAVIGUI::InterfaceManager::addObject(cornerButton2);
    cornerButton3 = new EAVIGUI::ImageButton(this, CORNERBUTTON3, 0, 0, "cornerButton.png", "cornerButtonT.png");
    cornerButton3->setRelativePositioning(1.0, -cornerButton3->getScaledHeight(), 0.0 , 0.0);
    cornerButton3->setColor(ofColor(255,255,255,170));
    cornerButton3->setCanTouchTranparency(true);
    EAVIGUI::InterfaceManager::addObject(cornerButton3);
    cornerButton4 = new EAVIGUI::ImageButton(this, CORNERBUTTON4, 0, 0, "cornerButton.png", "cornerButtonT.png");
    cornerButton4->setRelativePositioning(0, 0, 0, 0);
    cornerButton4->setColor(ofColor(255,255,255,170));
    cornerButton4->setCanTouchTranparency(true);
    EAVIGUI::InterfaceManager::addObject(cornerButton4);

    EAVIGUI::InterfaceManager::setup();
    svMenu.setup(this, &grid);
    updateScene(gridX, gridY);
    
    ((scenePlay*)grid[1][1])->setLooped(true);
    ((sceneAccelStretch*) grid[2][2])->setMotionTriggering(true);
    ((sceneAccelStretch*) grid[3][2])->setMotionTriggering(true);
    ((sceneAccelStretch*) grid[4][2])->setMotionTriggering(true);

    ((sceneAccelStretch*) grid[2][3])->setMotionTriggering(true);
    ((sceneAccelStretch*) grid[3][3])->setMotionTriggering(true);
    ((sceneAccelStretch*) grid[4][3])->setMotionTriggering(true);
    
    ((sceneAccelStretch*) grid[2][2])->setThreshold(sceneAccelStretch::THRESHLOW);
    ((sceneAccelStretch*) grid[3][2])->setThreshold(sceneAccelStretch::THRESHLOW);
    ((sceneAccelStretch*) grid[4][2])->setThreshold(sceneAccelStretch::THRESHLOW);

    ((sceneAccelStretch*) grid[2][3])->setThreshold(sceneAccelStretch::THRESHHIGH);
    ((sceneAccelStretch*) grid[3][3])->setThreshold(sceneAccelStretch::THRESHHIGH);
    ((sceneAccelStretch*) grid[4][3])->setThreshold(sceneAccelStretch::THRESHHIGH);
    

    maxiSettings::setup(44100, 1, 1024);
    dcBlockTotal = 0;
    bleFrameCount = 0;
    bleMeterSize = ofGetWidth()/20.0;
    bleVals.resize(NUMNBSTREAMS);
    for(int i=0; i < NUMNBSTREAMS; i++) {
        bleMA[i].resize(3);
    }
    if (useNoiseBear) {
        scanner = [[BLEScanner alloc] init];
        [scanner startScanning];
    }

}

void SonicTag3App::onValueUpdate() {
    NSData *val;
    val = [scanner value];
    if ([val length] == 17 && [val bytes] != NULL) {
        unsigned short *data = (unsigned short*) [val bytes];
        unsigned char *chardata = (unsigned char*) [val bytes];
        int batch = (int) chardata[16];
        if (bleFrameCount > 4) {
            int offset = (batch * 8);
            for(int i=0; i < 8; i++) {
                int idx = i + offset;
                vals[idx] = data[i];
                if (vals[idx] > 65400)
                    vals[idx] = 0;  // dropped contact
                if (bleFrameCount == 5) {
                    bleMA[idx].fillWith(vals[idx]);
                }else{
                    bleMA[idx].addSample(vals[idx]);
                }
                nbStreams[idx].newVal(bleMA[idx].value());
                bleVals[i] = nbStreams[i].getValue();
                dcBlockTotal += dcblock[idx].play(powf(nbStreams[idx].getValue(), 0.5f), 0.88);
            }
        }
        if (batch == 1) {
            bleFrameCount++;
            float sigAvg = dcBlockTotal / NUMNBSTREAMS;
            sigAvg = dcMasterBlocker.play(sigAvg, 0.88);
            grid[gridX][gridY]->updateBLEVals(bleVals, sigAvg);
            dcBlockTotal = 0;
        }
    }
    
}


//--------------------------------------------------------------
void SonicTag3App::update(){
    switch(appPhase) {
        case LOADING:
                updateScene(gridX, gridY);
                appPhase = REMIX; //!
            break;
        case REMIX:
            if (NULL != grid[gridX][gridY]) {
                grid[gridX][gridY]->update();
                if (canProgressChange.newFrame(grid[gridX][gridY]->canProgress() ? 1 : 0)) {
                    setNavVisibility();
                }
            }
            break;
    }
}

//--------------------------------------------------------------
void SonicTag3App::draw(){
    ofBackground(255);
    ofSetColor(255,255,255);
    grid[gridX][gridY]->draw();

    //ble meter
    ofFill();
    for(int i=0; i < bleVals.size(); i++) {
        ofSetColor(i*50 % 255, i*200 % 255, i * 150 % 255, bleVals[i] * 255.0);
        ofRect(10 + (i * bleMeterSize), ofGetHeight() - 10 - bleMeterSize, bleMeterSize, bleMeterSize);
    }
    
}

void SonicTag3App::audioRequested( float * output, int bufferSize, int nChannels ) {
    if (sceneIsUpdating) {
        for(int i=0; i < bufferSize; i++) {
            output[i] *= 0.2;
        }
    }else{
        grid[gridX][gridY]->audioRequested(output, bufferSize, nChannels);
        for(int i=0; i < bufferSize; i++) {
            sharedData.mir.play(output[i]);
        }
    }
}

void SonicTag3App::audioIn( float * input, int bufferSize, int nChannels ) {
    grid[gridX][gridY]->audioIn(input, bufferSize, nChannels);
}

//--------------------------------------------------------------
void SonicTag3App::exit(){
    ofSoundStreamStop();
    if (sharedData.soundRecorded) {
        sharedData.buffer.save(autoSaveName.str());
        cout << "Autosaved\n";
//        log::save();
    }
}

//--------------------------------------------------------------
void SonicTag3App::touchDown(ofTouchEventArgs &touch){
    grid[gridX][gridY]->touchDown(touch);
}

//--------------------------------------------------------------
void SonicTag3App::touchMoved(ofTouchEventArgs &touch){
    grid[gridX][gridY]->touchMoved(touch);
}

//--------------------------------------------------------------
void SonicTag3App::touchUp(ofTouchEventArgs &touch){
    grid[gridX][gridY]->touchUp(touch);
}

//--------------------------------------------------------------
void SonicTag3App::touchDoubleTap(ofTouchEventArgs &touch){
    grid[gridX][gridY]->touchDoubleTap(touch);
}

//--------------------------------------------------------------
void SonicTag3App::lostFocus(){

}

//--------------------------------------------------------------
void SonicTag3App::gotFocus(){

}

//--------------------------------------------------------------
void SonicTag3App::gotMemoryWarning(){

}

//--------------------------------------------------------------
void SonicTag3App::deviceOrientationChanged(int newOrientation){
    grid[gridX][gridY]->currentOrientation=newOrientation;

}


//--------------------------------------------------------------
void SonicTag3App::touchCancelled(ofTouchEventArgs& args){
    grid[gridX][gridY]->touchCancelled(args);
}

void SonicTag3App::updateScene(int sceneX, int sceneY) {
    //if this a valid scene?
    bool validScene = (sceneX >=0 && sceneX < grid.size() && sceneY >= 0 && sceneY < grid[0].size());
    //further confirmation
    if (validScene)
        validScene = grid[sceneX][sceneY] != NULL;
    
    if(!sceneIsUpdating && validScene) {
        //thread lock
        sceneIsUpdating = true;
        if (isASceneStartedYet) {
            grid[gridX][gridY]->endScene();
            
        }
        
        gridX = maxiMap::clamp<int>(sceneX, 0, grid.size()-1);
        gridY = maxiMap::clamp<int>(sceneY, 0, grid[0].size()-1);
        canProgressChange.value = 1;
        navLeftArrow->setVisible(false);
        navRightArrow->setVisible(false);
        navUpArrow->setVisible(false);
        navDownArrow->setVisible(false);
        
        tempLockNavigation = false; //make sure nav will be visible if not permenantly locked
        setNavVisibility();
        
        grid[gridX][gridY]->beginScene();
        isASceneStartedYet = true;

        log::write(log::NEWSCENE, grid[gridX][gridY]->getTitle());
        sceneIsUpdating = false;
        svMenu.setLocation(gridX, gridY);
    }
}

void SonicTag3App::setNavVisibility() {
    if (lockNavigation || tempLockNavigation) {
        navLeftArrow->setVisible(false);
        navRightArrow->setVisible(false);
        navUpArrow->setVisible(false);
        navDownArrow->setVisible(false);
    }else{
        bool vis = false;
        if (NULL != grid[gridX][gridY])
            vis = grid[gridX][gridY]->canProgress();
        if (gridX > 0) {
            if (grid[gridX - 1][gridY] != NULL) {
                if (grid[gridX - 1][gridY]->enabled) {
                    navLeftArrow->setVisible(vis);
                }
            }
        }
        if (gridX < grid.size() - 1) {
            if (grid[gridX + 1][gridY] != NULL) {
                if (grid[gridX + 1][gridY]->enabled) {
                    navRightArrow->setVisible(vis);
                }
            }
        }
        if (gridY > 0) {
            if (grid[gridX][gridY - 1] != NULL) {
                if (grid[gridX][gridY - 1]->enabled) {
                    navUpArrow->setVisible(vis);
                }
            }
        }
        if (gridY < grid[gridX].size() - 1) {
            if (grid[gridX][gridY + 1] != NULL) {
                if (grid[gridX][gridY + 1]->enabled) {
                    navDownArrow->setVisible(vis);
                }
            }
        }
    }
}

void SonicTag3App::handleInterfaceEvent(int id, int eventTypeId, EAVIGUI::InterfaceObject *object) {
    if (eventTypeId != EAVIGUI::InterfaceObject::TOUCHMOVED)
        cout << "Interface event, object " << id << ", event: " << eventTypeId << endl;
    switch(id) {
        case LEFTARROW:
            switch(eventTypeId) {
                case EAVIGUI::InterfaceObject::TOUCHUP:
                    updateScene(gridX - 1, gridY);
                    break;
                default: ;
            }
            break;
        case RIGHTARROW:
            switch(eventTypeId) {
                case EAVIGUI::InterfaceObject::TOUCHUP:
                    updateScene(gridX + 1, gridY);
                    break;
                default: ;
            }
            break;
        case UPARROW:
            switch(eventTypeId) {
                case EAVIGUI::InterfaceObject::TOUCHUP:
                    updateScene(gridX, gridY - 1);
                    break;
                default: ;
            }
            break;
        case DOWNARROW:
            switch(eventTypeId) {
                case EAVIGUI::InterfaceObject::TOUCHUP:
                    updateScene(gridX, gridY + 1);
                    break;
                default: ;
            }
            break;
        case NAVMENU:
            switch(eventTypeId) {
                case EAVIGUI::InterfaceObject::TOUCHUP:
                    updateScene(0,0);
                    break;
                default: ;
            }
            break;
        case CORNERBUTTON1:
            switch(eventTypeId) {
                case EAVIGUI::InterfaceObject::TOUCHUP:
                    cornerButton2->setVisible(false);
                    cornerButton3->setVisible(false);
                    cornerButton4->setVisible(false);
                    break;
                case EAVIGUI::InterfaceObject::TOUCHDOWN:
                    cornerButton2->setVisible(true);
                    break;
                case EAVIGUI::InterfaceObject::TOUCHEXIT:
                    cornerButton2->setVisible(false);
                    cornerButton3->setVisible(false);
                    cornerButton4->setVisible(false);
                    break;
                default: ;
            }
            break;
        case CORNERBUTTON2:
            switch(eventTypeId) {
                case EAVIGUI::InterfaceObject::TOUCHUP:
                    cornerButton3->setVisible(false);
                    cornerButton4->setVisible(false);
                    break;
                case EAVIGUI::InterfaceObject::TOUCHDOWN:
                    cornerButton3->setVisible(true);
                    break;
                case EAVIGUI::InterfaceObject::TOUCHEXIT:
                    cornerButton3->setVisible(false);
                    cornerButton4->setVisible(false);
                    break;
                default: ;
            }
            break;
        case CORNERBUTTON3:
            switch(eventTypeId) {
                case EAVIGUI::InterfaceObject::TOUCHUP:
                    cornerButton4->setVisible(false);
                    break;
                case EAVIGUI::InterfaceObject::TOUCHDOWN:
                    cornerButton4->setVisible(true);
                    break;
                case EAVIGUI::InterfaceObject::TOUCHEXIT:
                    cornerButton4->setVisible(false);
                    break;
                default: ;
            }
            break;
        case CORNERBUTTON4:
            switch(eventTypeId) {
                case EAVIGUI::InterfaceObject::TOUCHUP:
                    break;
                case EAVIGUI::InterfaceObject::TOUCHDOWN:
                    cornerButton2->setVisible(false);
                    cornerButton3->setVisible(false);
                    cornerButton4->setVisible(false);
                    svMenu.setVisible(true);
                    break;
                case EAVIGUI::InterfaceObject::TOUCHEXIT:
                    break;
                default: ;
            }
            break;
        case supervisorMenu::DONEBUTTON:
            switch(eventTypeId) {
                case EAVIGUI::InterfaceObject::TOUCHUP:
                    svMenu.setVisible(false);
                    break;
                default: ;
            }
            break;
        case supervisorMenu::LOCKCB:
            switch(eventTypeId) {
                case EAVIGUI::InterfaceObject::TOUCHUP:
                    lockNavigation = !static_cast<EAVIGUI::CheckBox*>(object)->isChecked();
                    setNavVisibility();
                    break;
            }
            break;
        case supervisorMenu::MAPCONTROL:
            switch(eventTypeId) {
                case EAVIGUI::MapControl::MAPCHANGESCENE:
                    int gx, gy;
                    svMenu.getLocation(gx, gy);
                    updateScene(gx, gy);
                    break;
            }
            break;
        case supervisorMenu::INFOBUTTON:
            switch(eventTypeId) {
                case EAVIGUI::InterfaceObject::TOUCHUP:
                    svMenu.setVisible(false);
                    svMenu.showInfo(true);
                    break;
            }
            break;
        case supervisorMenu::INFOLABEL:
            switch(eventTypeId) {
                case EAVIGUI::InterfaceObject::TOUCHUP:
                    svMenu.showInfo(false);
                    break;
            }
            break;
    }
    
}

void SonicTag3App::gotMessage(ofMessage& msg) {
    if (msg.message == "temphidenav") {
        cout << msg.message << endl;
        tempLockNavigation = true;
        setNavVisibility();
    }
    if (msg.message == "tempshownav") {
        cout << msg.message << endl;
        tempLockNavigation = false;
        setNavVisibility();
    }
}

