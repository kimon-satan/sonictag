//
//  scenePlay.h
//  sonicTag2
//
//  Created by Chris Kiefer on 27/06/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#ifndef sonicTag2_scenePlay_h
#define sonicTag2_scenePlay_h

#include "baseScene.h"
#include "ofxMaxim.h"
#include <vector>
#include "visualiser.h"
#include "geomFunctions.h"
#include "MfccVisualiser.h"

using namespace std;

class scenePlay : public baseScene {
public:
    void setup(sharedDataContainer *data);
    void update();
    void draw();
    void audioRequested( float * output, int bufferSize, int nChannels );
    void audioIn( float * input, int bufferSize, int nChannels );
    void touchDown(ofTouchEventArgs &touch);
	void touchUp(ofTouchEventArgs &touch);
    void beginScene();
    void endScene();
    string getTitle() {return string("Play").append(loop ? " looped" : "");}
    void setLooped(bool newValue);
    ofImage undo, redo;
    ofPoint undoPos, redoPos;
    void setUndoRedoVisibility(bool show);
    void handleInterfaceEvent(int id, int eventTypeId, EAVIGUI::InterfaceObject *object);
    void updateBLEVals(vector<float> newVals, float sigAvg);

protected:
    void play();
    bool loop;
    bool showUndoRedo;
    EAVIGUI::MfccVisualiser *mfccVis;
    EAVIGUI::ImageButton *histBackBtn, *histForwardBtn;
    enum GUIDS {HISTBACK, HISTFORWARD, VISUALISER};
    EAIT::BasicTriggerF nbEnergyTrigger;
    

private:
    int pos;
    bool playing;
    visualiser vis;
    ofPoint prevButtonCentre, nextButtonCentre;
    
};



#endif
