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
#include "waveform.h"
namespace EAVIGUI {

    Waveform::Waveform(InterfaceListener *_listener, int _id, int _x, int _y, int _w, int _h) :
    InterfaceObject(_listener, _id, _x, _y, _w, _h)
    {
        ofFbo::Settings settings;
        settings.width			= 256;
        settings.height			= 128;
        fboWidth = settings.width;
        fboHeight = settings.height;
        settings.useDepth		= false;
        settings.useStencil		= false;
        waveFBO.allocate(settings);    
        pos = 0;
    }

    
    void Waveform::drawToBuffer() {
        ofFill();
        ofSetColor(10,10,10,230);
        ofRect(0,0,w,h);
        ofSetColor(255,255,255,255);
        waveFBO.draw(0,0,w,h);
        ofSetColor(0, 0, 255,200);
        ofLine(pos, 0, pos, h);
    }
    
    void Waveform::updatePos(float _pos) {
        pos = (_pos * (float)w);
        invalidate();
    }

    
    void Waveform::updateWaveform(maxiSample *sample) {
        float inc =  (sample->length - 1) / (float)fboWidth;
        waveFBO.begin();
        int x=0;
        ofClear(255);
        ofSetColor(255,255,255,255);
        for(float i=0; i < sample->length; i += inc) {
            ofLine(x, fboHeight / 2, x, (fboHeight / 2) + (sample->temp[static_cast<int>(floor(i))] / 32767.0 * (fboHeight / 2) * 2.0));
            x++;
        }
        waveFBO.end();
    }


};