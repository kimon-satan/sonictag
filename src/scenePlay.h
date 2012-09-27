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
#include "HeadVisualiser.h"
#include "audioProcessor.h"

using namespace std;

class audioProcessorPlay : public audioProcessor {
public:
    audioProcessorPlay();
    float play(float input);
};


class scenePlay : public baseScene {
public:
    void setup(sharedDataContainer *data);
    void update();
    void draw();
    void touchDown(ofTouchEventArgs &touch);
	void touchUp(ofTouchEventArgs &touch);
    void beginScene();
    void endScene();
    string getTitle() {return string("Play");}
    audioProcessor* getAudioProcessor() {return new audioProcessorPlay();};
protected:
private:
    int pos;
    bool playing;
//    visualiser vis;
    EAVIGUI::HeadVisualiser *headVis;
};



#endif
