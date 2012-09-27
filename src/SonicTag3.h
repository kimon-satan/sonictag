//
//  DRSAppIOS.h
//  DRSAppIOS
//
//  Created by Chris Kiefer on 20/08/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#ifndef DRSAppIOS_DRSAppIOS_h
#define DRSAppIOS_DRSAppIOS_h

#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "SonicTag3App.h"

//#define LATCHMODE

class SonicTag3 : public ofxiPhoneApp{
	
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

    SonicTag3App app;
    
};




#endif
