//
//  sceneVBirth.h
//  DRSApp
//
//  Created by Chris Kiefer on 26/07/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#ifndef DRSApp_sceneVBirth_h
#define DRSApp_sceneVBirth_h

#include "baseScene.h"
#include "assets.h"

class sceneVBirth : public baseScene {
public:
    void setup(sharedDataContainer *data);
    void setupNewTrack();
    void update();
    void draw();
    void audioRequested( float * output, int bufferSize, int nChannels );
    void audioIn( float * input, int bufferSize, int nChannels ); 
    void touchDown(ofTouchEventArgs &touch);
	void touchMoved(ofTouchEventArgs &touch);
	void touchUp(ofTouchEventArgs &touch);
	void touchDoubleTap(ofTouchEventArgs &touch);
	void touchCancelled(ofTouchEventArgs &touch);
    void beginScene();
    void endScene();
    string getSubTitle() {return "Add a new track to your remix!";};
    int getNewAudioTrackNumber();
    ofImage getHead(int headId);
    string getTitle();
    void handleInterfaceEvent(int id, int eventTypeId, EAVIGUI::InterfaceObject *object);
    bool canProgress();
private:
    vector<EAVIGUI::ImageButton*> heads;
    vector<EAIT::MovingAverageF> headRadius, mixLevels;
    vector<maxiEnvelopeFollower> envs;
//    vector<float> mixLevels;
    int currTrack;
    void setHeadPositions();
    EAVIGUI::Label *instructions;
    bool firstRun;
    EAVIGUI::InterfaceObjectGroup instructionsModal;
    EAVIGUI::ImageButton *mapIcon;
    int maxTracks;
};

#endif
