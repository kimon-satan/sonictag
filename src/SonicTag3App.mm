#include "SonicTag3App.h"
#include <sstream>
#include "sharedData.h"
#include "sceneRecord.h"
//#include "scenePlay.h"
#include "sceneLoopRecord.h"
//#include "sceneFingerPlay.h"
//#include "sceneFingerPlayPitch.h"
#include "sceneFingerStretch.h"
#include "sceneFingerPitch.h"
#include "sceneFingerPitchStretch.h"
#include "sceneVBirth.h"
#include "sceneGain.h"
#include "sceneFilter.h"
#include "sceneDistort.h"
#include "audioCatalogue.h"
#include "log.h"

const int trigTime = 50;

//--------------------------------------------------------------
void SonicTag3App::setup(){	
    
    ofRegisterGetMessages(this);
    appPhase = MAP;
    sampleCounter=0;
    ofSetLogLevel(OF_LOG_WARNING);

	
	//If you want a landscape oreintation 
	//iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
    
#ifdef TARGET_OF_IPHONE 
    log::init(ofxiPhoneGetDocumentsDirectory());
#else
    log::init(ofToDataPath(""));
#endif    
    
    mimiLoop.load(ofToDataPath("mimiLoop.wav"));
    mimiGrains = new DRSmaxiPitchStretch<float, DRShannWinFunctor<float> >(&mimiLoop);
    setMIMIStretch();
    assets::setup();
    
//    introVid.loadMovie("DRSVid.mp4");
    
    sceneIsUpdating = false;
    
    sharedData.currentDimension = DRSDATA::BRAZIL;
    
    stringstream bdfile;
    bdfile << "backdrops/" << assets::dimensions[sharedData.currentDimension].backdrop << ".png";
    sharedData.backdrop.loadImage(bdfile.str());
//    sharedData.backdrop.loadImage("phantasmagoria backdrop.png");

    //GUI
    navFont.loadFont("LARABIEF.TTF", 80);
    navFontSmall.loadFont("mono.ttf", 25);

#ifndef TARGET_OF_IPHONE
    EAVIGUI::InterfaceManager::redirectMouseToTouch = true;
#endif
    
    EAVIGUI::InterfaceManager::deviceScaleMod = 1.0;
#ifdef TARGET_OF_IPHONE
    UIDevice* thisDevice = [UIDevice currentDevice];
    if(thisDevice.userInterfaceIdiom == UIUserInterfaceIdiomPad)
    {
        EAVIGUI::InterfaceManager::deviceScaleMod = 1.0;
    }
    else
    {
        EAVIGUI::InterfaceManager::deviceScaleMod = 0.41;
    }    
#endif
    
    EAVIGUI::InterfaceManager::addFont("titles", "ka1.ttf", 30);
    EAVIGUI::InterfaceManager::addFont("subtitles", "PixelSplitter-Bold.ttf", 12);
    EAVIGUI::InterfaceManager::addFont("big", "ka1.ttf", 50);
    EAVIGUI::InterfaceManager::addFont("bigger", "ka1.ttf", 60);
    EAVIGUI::InterfaceManager::addFont("c64Rounded", "Commodore Rounded v1.2.ttf", 20);

    
    audioCatalogue::scan();
    audioCatalogue::deleteOldRecordings();
    
    backzoom = new EAVIGUI::ZoomScreenImage(this, BACKZOOM, 0, 0, &sharedData.backdrop);
    EAVIGUI::InterfaceManager::addObject(backzoom);

    navButtonSize = 90;
    navLeftArrow = (new EAVIGUI::ImageButton(this, LEFTARROW, 0, 0, "arrowleftS.png"));
    navLeftArrow->setRelativePositioning(0, 0, 0.5, -(navLeftArrow->getScaledHeight() / 2.0));
    navLeftArrow->setAnchorPoint(0, 0);
    navLeftArrow->pulsate = true;
    navLeftArrow->fadeTime = 100;
    EAVIGUI::InterfaceManager::addObject(navLeftArrow);
    
    navRightArrow = new EAVIGUI::ImageButton(this, RIGHTARROW, 0, 0, "arrowrightS.png");
    navRightArrow->setRelativePositioning(1.0, -navRightArrow->getScaledWidth(), 0.5, -(navRightArrow->getScaledHeight() / 2.0));
    navRightArrow->setAnchorPoint(0, 0);
    navRightArrow->pulsate = true;
    navRightArrow->fadeTime = 100;
    EAVIGUI::InterfaceManager::addObject(navRightArrow);
    
    navUpArrow = new EAVIGUI::ImageButton(this, UPARROW, 0, 0, "arrowupS.png");
    navUpArrow->setRelativePositioning(0.5, -(navUpArrow->getScaledWidth()/2.0), 0, 0);
    navUpArrow->setAnchorPoint(0, 0);
    navUpArrow->pulsate = true;
    navUpArrow->fadeTime = 100;
    EAVIGUI::InterfaceManager::addObject(navUpArrow);
    
    navDownArrow = new EAVIGUI::ImageButton(this, DOWNARROW, 0, 0, "arrowdownS.png");
    navDownArrow->setRelativePositioning(0.5, -(navDownArrow->getScaledWidth() / 2.0), 1.0, -navDownArrow->getScaledHeight());
    navDownArrow->setAnchorPoint(0, 0);
    navDownArrow->pulsate = true;
    navDownArrow->fadeTime = 100;
    EAVIGUI::InterfaceManager::addObject(navDownArrow);
    
    navMenuButton = new EAVIGUI::ImageButton(this, NAVMENU, 0, 0, "DFE---dean-standing-icon.png");
    navMenuButton->setRelativePositioning(1.0, -navMenuButton->getScaledWidth(), 1.0, -navMenuButton->getScaledHeight());
    navLeftArrow->setAnchorPoint(0, 0);
    navMenuButton->fadeTime = 50;
    EAVIGUI::InterfaceManager::addObject(navMenuButton);
    
    wavform = new EAVIGUI::Waveform(this, WAV, 0, 0, 300, 100);
    wavform->setRelativePositioning(0.99, -wavform->getScaledWidth(), 0.02, 0);
    EAVIGUI::InterfaceManager::addObject(wavform);
	
    isRecording = false;
    isRecordingOutput = false;
    
    //recover autosave
//    autoSaveName << ofxiPhoneGetDocumentsDirectory() << "autosave" << ".wav";    
//    sharedData.buffer.load(autoSaveName.str());
    
    int gridWidth=6;
    int gridHeight = 1;
    grid.resize(gridWidth);
    for(int i=0; i < grid.size(); i++) {
        grid[i].resize(gridHeight, NULL);
    }
    gridX = 0;
    gridY = 0;    
    isASceneStartedYet = false;

    grid[0][0] = new sceneVBirth();
    //    grid[1][0] = new scenePlay();
    grid[1][0] = new sceneFingerStretch();
    grid[2][0] = new sceneFingerPitch();
//    grid[2][0] = new sceneGain();
    grid[3][0] = new sceneGain();
    grid[4][0] = new sceneFilter();
    grid[5][0] = new sceneDistort();
    
    for(int i=0; i < grid.size(); i++) {
        for(int j=0; j < grid[i].size(); j++) {
            if (grid[i][j] != NULL) {
                grid[i][j]->setup(&sharedData);
                grid[i][j]->enabled = true;
            }
        }
    }
    
    dmap.setup(&sharedData);
    
    filterFreq = 1.0;
    pitchRange = 1.0;
    rateRange = 1.0;
    buttonTrigTime = 0;
    waitingForTrig = false;
    

    
    EAVIGUI::InterfaceManager::setup();
    
    maxiSettings::setup(44100, 1, 1024);

//    introVid.play();
    
}

//--------------------------------------------------------------
void SonicTag3App::update(){
    switch(appPhase) {
        case INTROVIDEO:
//            introVid.update();
            break;
        case MAP:
            break;
        case PRELOADING:
            oggLoader.startThread(false, false);
            appPhase = LOADING;
        case LOADING:
            if (oggLoader.finished) {
                oggLoader.stopThread();
                backzoom->invalidate();
                sharedData.audioLoaded = true;
                slots.resize(sharedData.audioTracks.size(), NULL);
                sharedData.barLength = 60.0 / sharedData.currSong->bpm * sharedData.currSong->beatsPerBar * maxiSettings::sampleRate;
                cout << "Bar length: " << sharedData.barLength << endl;

                dmap.showHide(false);
                ((sceneVBirth*)grid[0][0])->setupNewTrack();
                gridX = 0;
                gridY = 0;
                updateScene(gridX, gridY);
                backzoom->setVisible(true);
                appPhase = REMIX; //!
            }
            break;
        case REMIX:
            if (NULL != grid[gridX][gridY]) {
                grid[gridX][gridY]->update();
                if (canProgressChange.newFrame(grid[gridX][gridY]->canProgress() ? 1 : 0)) {
                    setNavVisibility();
                }
                if (gridX>0 || gridY > 0)
                    wavform->updatePos(((audioProcessorTimeStretch*)sharedData.currSampleInstance->audioFlow[0])->pitchStretch->position / (float) sharedData.currSampleInstance->sample.length);
            }
            break;
    }
}

//--------------------------------------------------------------
void SonicTag3App::draw(){
    ofBackground(255);
    switch(appPhase) {
        case INTROVIDEO:
            ofSetColor(255, 255, 255,255);
//            introVid.draw(0,0);
            break;
        case MAP:
            ofBackground(0);
            ofSetColor(255, 255, 255,255);
            break;     
        case LOADING:
            ofBackground(255);
            break;
        case REMIX:
            grid[gridX][gridY]->draw();
            ofSetColor(255,255,255);
            break;
    }
}

void SonicTag3App::audioRequested( float * output, int bufferSize, int nChannels ) {
    if (REMIX == appPhase) {
        if (0==gridX && 0 == gridY) {
            grid[0][0]->audioRequested(output, bufferSize, nChannels);    
        }else{
            //run all audioflows in all sample instances
            for(int i=0; i < bufferSize; i++) {
                float wave=0;
                for(int inst=0; inst < sharedData.sampleInstances.size(); inst++) {
                    float instOutput=0;
                    for(int processor=0; processor < sharedData.sampleInstances[inst]->audioFlow.size(); processor++) {
                        instOutput = sharedData.sampleInstances[inst]->audioFlow[processor]->play(instOutput);
                    }
                    sharedData.sampleInstances[inst]->mir.play(instOutput);
                    wave += instOutput;
                }
                wave /= sharedData.sampleInstances.size();
#ifdef TARGET_OF_IPHONE
                //limiter
                if (wave > 0.99) {
                    wave = 0.99;
                }else if (wave < -0.99) {
                    wave = -0.99;
                }
#endif
                output[i] = wave;
                if (sampleCounter % sharedData.barLength == 0) {
                    cout << "bar" << endl;
                    for(int gx=0; gx < grid.size(); gx++) {
                        for(int gy=0; gy < grid[gx].size(); gy++) {
                            if (grid[gx][gy] != NULL) {
                                grid[gx][gy]->onBarStart();
                            }
                        }
                    }
                }
                sampleCounter++;
            }
        }
    }else if (MAP == appPhase || LOADING == appPhase) {
        for(int i=0; i < bufferSize; i++) {
//            output[i] = mimiLoop.play();
            output[i] = mimiGrains->play(1, mimiStretch, 0.08, 2) * 0.7;
        }
    }
}

void SonicTag3App::audioIn( float * input, int bufferSize, int nChannels ) {
//    grid[gridX][gridY]->audioIn(input, bufferSize, nChannels);
}

//--------------------------------------------------------------
void SonicTag3App::exit(){
    sharedData.buffer.save(autoSaveName.str());
    cout << "Autosaved\n";
    log::save();
    delete mimiGrains;
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
        bool leavingVBirth = gridX==0 && gridY==0;
        if (isASceneStartedYet) {
            grid[gridX][gridY]->endScene();
            
            if (leavingVBirth) {
                //it's a vbirth
                //create sample instance
                int sampleIndex = ((sceneVBirth*)grid[0][0])->getNewAudioTrackNumber();
                if(NULL==slots[sampleIndex]) {
#ifdef TARGET_OF_IPHONE                
                    if ([UIDevice currentDevice].userInterfaceIdiom == UIUserInterfaceIdiomPhone) {
                        //limit number of concurrent tracks
                        if (6 == sharedData.sampleInstances.size()) {
                            //remove bottom
                            cout << "Removing 1 track from SI size " << sharedData.sampleInstances.size() << "\n";
                            //empty slot
                            slots[sharedData.sampleInstances[0]->slot] = NULL;
                            sharedData.sampleInstances.erase(sharedData.sampleInstances.begin());
                        }
                    }
#endif                    
                    
                    sampleInstance *newSampleInst = new sampleInstance(sharedData.audioTracks[sampleIndex]);
                    newSampleInst->icon = ((sceneVBirth*)grid[0][0])->getHead(sampleIndex);
                    
                    //create an audio chain
                    for(int i=0; i < grid.size(); i++) {
                        for(int j=0; j < grid[0].size(); j++) {
                            if (i > 0 || j > 0) { //skip the vbirth scene
                                if (NULL != grid[i][j]) {
                                    audioProcessor *newProcessor = grid[i][j]->getAudioProcessor();
                                    newProcessor->sceneID = grid[i][j]->getSceneID();
                                    newProcessor->setSample(&newSampleInst->sample, sharedData.currSong->lengthInBars);
                                    newSampleInst->audioFlow.push_back(newProcessor);
                                }
                            }
                        }
                    }
                    
                    newSampleInst->slot = sampleIndex;
                    sharedData.sampleInstances.push_back(newSampleInst);
                    sharedData.currSampleInstance = newSampleInst;
                    slots[sampleIndex] = newSampleInst;
                }else{
                    //already have an instance of this track
                    sharedData.currSampleInstance = slots[sampleIndex];
                    sceneX = sharedData.currSampleInstance->gridX;
                    sceneY = sharedData.currSampleInstance->gridY;
                    cout << "Moving to " << sceneX << "," << sceneY << endl;
                }
                wavform->updateWaveform(&sharedData.currSampleInstance->sample);

            }
        }
        
        gridX = maxiMap::clamp<int>(sceneX, 0, grid.size()-1);
        gridY = maxiMap::clamp<int>(sceneY, 0, grid[0].size()-1);
        canProgressChange.value = 1;
        navLeftArrow->setVisible(false);
        navRightArrow->setVisible(false);
        navUpArrow->setVisible(false);
        navDownArrow->setVisible(false);
        
        navMenuButton->setVisible(gridX > 0 || gridY > 0);
        wavform->setVisible(gridX > 0 || gridY > 0);

        setNavVisibility();
        
        audioProcessor *currProcessor=NULL;
        if (NULL != sharedData.currSampleInstance) {
            //find audio processor to match the current scene
            for(int i=0; i < sharedData.currSampleInstance->audioFlow.size(); i++) {
                if (sharedData.currSampleInstance->audioFlow[i]->sceneID == grid[gridX][gridY]->getSceneID()) {
                    currProcessor = sharedData.currSampleInstance->audioFlow[i];
                    break;
                }
            }
            //track the position of this sample instance
            if(gridX != 0 || gridY != 0) {
                sharedData.currSampleInstance->gridX = gridX;
                sharedData.currSampleInstance->gridY = gridY;
            }
        }
        grid[gridX][gridY]->setAudioProcessor(currProcessor);
        grid[gridX][gridY]->beginScene();    
        isASceneStartedYet = true;

        log::write(log::NEWSCENE, grid[gridX][gridY]->getTitle());
        sceneIsUpdating = false;
    }
}

void SonicTag3App::setNavVisibility() {
    bool vis = false;
    if (NULL != grid[gridX][gridY])
        vis = grid[gridX][gridY]->canProgress();
    if (gridX > 0) {
        if (grid[gridX - 1][gridY] != NULL) {
            if (grid[gridX - 1][gridY]->enabled) {
                //navLeftEnabled = true;
                navLeftArrow->setVisible(vis);
            }
        }
    }
    if (gridX < grid.size() - 1) {
        if (grid[gridX + 1][gridY] != NULL) {
            if (grid[gridX + 1][gridY]->enabled) {
                //navRightEnabled = true;
                navRightArrow->setVisible(vis);
            }
        }
    }
    if (gridY > 0) {
        if (grid[gridX][gridY - 1] != NULL) {
            if (grid[gridX][gridY - 1]->enabled) {
                //navUpEnabled = true;
                navUpArrow->setVisible(vis);
            }
        }
    }
    if (gridY < grid[gridX].size() - 1) {
        if (grid[gridX][gridY + 1] != NULL) {
            if (grid[gridX][gridY + 1]->enabled) {
                //navDownEnabled = true;
                navDownArrow->setVisible(vis);
            }
        }
    }
    
}

void SonicTag3App::handleInterfaceEvent(int id, int eventTypeId, EAVIGUI::InterfaceObject *object) {
    //cout << "Interface event, object " << id << ", event: " << eventTypeId << endl;
    
    switch(eventTypeId) {
        case EAVIGUI::InterfaceObject::TOUCHUP:
            switch(id) {
                case LEFTARROW:
                        updateScene(gridX - 1, gridY);
                    break;
                case RIGHTARROW:
                    updateScene(gridX + 1, gridY);
                    break;
                case UPARROW:
                    updateScene(gridX, gridY - 1);
                    break;
                case DOWNARROW:
                    updateScene(gridX, gridY + 1);
                    break;
                case NAVMENU:
                    updateScene(0,0);
                    break;
            }
            break;
    }
}

void SonicTag3App::gotMessage(ofMessage& msg) {
    cout << "Msg: " << msg.message << endl;
    if ("resync" == msg.message) {
        for(int inst=0; inst < sharedData.sampleInstances.size(); inst++) {
            for(int processor=0; processor < sharedData.sampleInstances[inst]->audioFlow.size(); processor++) {
                sharedData.sampleInstances[inst]->audioFlow[processor]->resync();
            }
        }
    }else if ("load" == msg.message) {
        cout << "Load\n";
        stringstream bdfile;
        bdfile << "backdrops/" << assets::dimensions[sharedData.currentDimension].backdrop << ".png";
        sharedData.backdrop.loadImage(bdfile.str());

        sharedData.audioLoaded = false;
        //clear old audio tracks
        sharedData.audioTracks.clear();
        for(int i=0; i < sharedData.sampleInstances.size(); i++) {
            delete sharedData.sampleInstances[i];
        }
        sharedData.sampleInstances.clear();
        sharedData.currSampleInstance = NULL;
        for(int i=0; i < slots.size(); i++)
            slots[i] = NULL;
        isASceneStartedYet = false;
        
        oggLoader.sharedData = &sharedData;
        appPhase = PRELOADING;
        
    }else if ("map" == msg.message) {
        if (appPhase != MAP) {
            cout << "back to map\n";
            setMIMIStretch();
            grid[gridX][gridY]->endScene();        
            backzoom->setVisible(false);
            navMenuButton->setVisible(false);
            navLeftArrow->setVisible(false);
            navRightArrow->setVisible(false);
            navUpArrow->setVisible(false);
            navDownArrow->setVisible(false);
            appPhase = MAP;
            dmap.show();
        }
    }
}

void SonicTag3App::setMIMIStretch() {
    mimiStretch = (ofRandomuf() * 1.5) + 0.001;
}


/////////////////////////

void SonicTag3App::oggLoadingThread::threadedFunction() {
    finished = false;
    yield();
    int loopLength = (60.0 / sharedData->currSong->bpm) * sharedData->currSong->beatsPerBar * sharedData->currSong->lengthInBars * maxiSettings::sampleRate;
    sharedData->audioTracks.resize(sharedData->currSong->parts.size());
    for(int i=0; i < sharedData->currSong->parts.size(); i++) {
        yield();
        stringstream filename;
        filename << "audio/" << assets::dimensions[sharedData->currentDimension].folder << "/" << sharedData->currSong->folder << "/";
        filename << sharedData->currSong->parts[i].filename << ".ogg";
        sharedData->audioTracks[i].loadOgg(ofToDataPath(filename.str()));
        sharedData->audioTracks[i].setLength(loopLength);
    }    
    finished = true;
}
