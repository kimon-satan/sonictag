//
//  SonicTag3.cpp
//  SonicTag3
//
//  Created by Chris Kiefer on 20/08/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#include <iostream>
#include "SonicTag3.h"

void SonicTag3::setup() {
	// register touch events
	ofRegisterTouchEvents(this);
	
	// initialize the accelerometer
	ofxAccelerometer.setup();
	
	//iPhoneAlerts will be sent to this.
	ofxiPhoneAlerts.addListener(this);

    app.setup();
    
	ofSoundStreamSetup(maxiSettings::channels, maxiSettings::channels,this, maxiSettings::sampleRate, maxiSettings::bufferSize, 4);
//    //disable audio input so iphone version works
//	ofSoundStreamSetup(maxiSettings::channels, 0,this, maxiSettings::sampleRate, maxiSettings::bufferSize, 4);
    
}

void SonicTag3::update() {
    app.update();
}

void SonicTag3::draw() {
    app.draw();
}

void SonicTag3::exit() {
    app.exit();
}

void SonicTag3::touchDown(ofTouchEventArgs &touch) {
    app.touchDown(touch);
}

void SonicTag3::touchMoved(ofTouchEventArgs &touch) {
    app.touchMoved(touch);
}

void SonicTag3::touchUp(ofTouchEventArgs &touch) {
    app.touchUp(touch);
}

void SonicTag3::touchDoubleTap(ofTouchEventArgs &touch) {
    app.touchDoubleTap(touch);
}

void SonicTag3::touchCancelled(ofTouchEventArgs &touch) {
    app.touchCancelled(touch);
}

void SonicTag3::lostFocus() {
    app.lostFocus();
}

void SonicTag3::gotFocus() {
    app.gotFocus();
}

void SonicTag3::gotMemoryWarning() {
    app.gotMemoryWarning();
}

void SonicTag3::deviceOrientationChanged(int newOrientation) {
    app.deviceOrientationChanged(newOrientation);
}

void SonicTag3::audioRequested( float * output, int bufferSize, int nChannels ) {
    app.audioRequested(output, bufferSize, nChannels);
}

void SonicTag3::audioIn( float * input, int bufferSize, int nChannels ) {
    app.audioIn(input, bufferSize, nChannels);
}


