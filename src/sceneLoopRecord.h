//
//  sceneLoopRecord.h
//  sonicTag2
//
//  Created by Chris Kiefer on 27/06/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#ifndef sonicTag2_sceneLoopRecord_h
#define sonicTag2_sceneLoopRecord_h

#include "baseScene.h"
#include "visualiser.h"

class sceneLoopRecord : public baseScene {
public:
    void setup(sharedDataContainer *data);
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
    virtual float getNextSample();
    string getTitle() {return "Loop Record";}  
protected:
    int clearCount;
    bool isRecording, isPlaying;
    visualiser vis;
};

#endif
