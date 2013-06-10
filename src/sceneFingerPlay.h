//
//  sceneFingerPlay.h
//  sonicTag2
//
//  Created by Chris Kiefer on 28/06/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#ifndef sonicTag2_sceneFingerPlay_h
#define sonicTag2_sceneFingerPlay_h

#include "sceneLoopRecord.h"
#include "ofxMaxim.h"

class sceneFingerPlay : public sceneLoopRecord {
public:
    void setup(sharedDataContainer *data);
    void update();
    void draw();
    void audioIn( float * input, int bufferSize, int nChannels );
    void touchDown(ofTouchEventArgs &touch);
	void touchMoved(ofTouchEventArgs &touch);
	void touchUp(ofTouchEventArgs &touch);
	void touchDoubleTap(ofTouchEventArgs &touch);
    void beginScene();
    void endScene();
    string getTitle() {return "Scratch";}
    
protected:
    float px, py, opx, opy;
    float velocity, velX, velY;
    int onCounter;
};



#endif
