//
//  waveform.cpp
//  DRSAppOSX
//
//  Created by Chris Kiefer on 30/08/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

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