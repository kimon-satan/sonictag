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


