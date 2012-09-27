//
//  sceneFingerPlay.h
//  sonicTag2
//
//  Created by Chris Kiefer on 28/06/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#ifndef sonicTag2_sceneFingerPlay_h
#define sonicTag2_sceneFingerPlay_h

#include "baseScene.h"
#include "ofxMaxim.h"
#include "HeadVisualiser.h"
#include "geomFunctions.h"

class sceneFingerPlay : public baseScene {
public:
    void setup(sharedDataContainer *data);    
    void update();
    void draw();
    void audioRequested( float * output, int bufferSize, int nChannels );
    void touchDown(ofTouchEventArgs &touch);
	void touchMoved(ofTouchEventArgs &touch);
	void touchUp(ofTouchEventArgs &touch);
	void touchDoubleTap(ofTouchEventArgs &touch);
    void beginScene();
    void endScene();
    string getTitle() {return "Scratch";}
    virtual float getNextSample();

protected:
    
    void processTouch(ofTouchEventArgs &touch);
    float px, py, opx, opy;
    float velocity, velX, velY;
    int onCounter;
    
    float angularVelocity, angle, lastAngle;   
    EAIT::MovingAverageF velMA;
    EAVIGUI::HeadVisualiser *headVis;
    maxiEnvelopeFollower envf;
    bool isPlaying;


};



#endif
