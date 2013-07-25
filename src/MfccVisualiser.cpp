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


#include "MfccVisualiser.h"

namespace EAVIGUI {
    
    MfccVisualiser::MfccVisualiser(InterfaceListener *_listener, int _id, int _x, int _y, int _w, int _h, sharedDataContainer *_data) : InterfaceObject(_listener, _id, _x, _y)
    {
        data = _data;
        setWidth(_w);
        setHeight(_h);
        init();
    }
    
    void MfccVisualiser::init() {
        radius = w/5.0;
        unit = radius / data->mir.mfccCoeffs.size();
        setIsInteractive(true);
        ofRegisterGetMessages(this);
    }
    
    void MfccVisualiser::update() {
        invalidate();
    }
    
    void MfccVisualiser::drawToBuffer() {
        ofSetCircleResolution(200);
        ofEnableAlphaBlending();
        for(int i=0; i < 4; i++) {
            ofSetColor(data->colours[i].r, data->colours[i].g, data->colours[i].b, val[i] * 255.0 * 2.0);
            ofCircle(cx, cy, (unit * (i*4)) + (val[i]*cx * 0.5));
        }
    }

    void MfccVisualiser::gotMessage(ofMessage &msg) {
        if (isVisible()) {
            if (msg.message == "fftcomplete") {
                for (int i=0; i < 4; i++) {
                    val[i]=interp[i].lopass(fabs(data->mir.mfccCoeffs[i+1]), 0.05 * fabs(data->mir.mfccCoeffs[i+1]));
                }
            }
        }
    }

}
