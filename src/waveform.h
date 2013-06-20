//
//  waveform.h
//  DRSAppOSX
//
//  Created by Chris Kiefer on 30/08/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#ifndef DRSAppOSX_waveform_h
#define DRSAppOSX_waveform_h

#include "EAVIGUI.interfaceObject.h"
#include <iostream>
#include "ofxMaxim.h"

using namespace std;

namespace EAVIGUI {
    
    class Waveform : public InterfaceObject {
    public:
        Waveform(InterfaceListener *_listener, int _id, int _x, int _y, int _w, int _h);
        void updateWaveform(maxiSample *sample);
        void updatePos(float _pos);
    protected:
        void drawToBuffer();
        ofFbo waveFBO;
        int fboWidth, fboHeight;
        float pos;
    private:
    };
    
};


#endif
