//
//  MfccVisualiser.cpp
//  SonicTag3
//
//  Created by Chris on 04/06/2013.
//
//

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
        radius = w/3.0;
        cx = w/2.0;
        cy = h/2.0;
        unit = radius / data->mir.mfccCoeffs.size();
        setIsInteractive(true);
        ofRegisterGetMessages(this);
    }
    
    void MfccVisualiser::update() {
        invalidate();
    }
    
    void MfccVisualiser::drawToBuffer() {
        ofSetCircleResolution(200);
        for(int i=0; i < 4; i++) {
            ofSetColor(data->colours[i].r, data->colours[i].g, data->colours[i].b, val[i] * 255.0 * 2.0);
            ofCircle(cx, cy, (unit * (i*4)) + (val[i]*cx * 0.5));
        }
    }

    void MfccVisualiser::gotMessage(ofMessage &msg) {
        if (isVisible()) {
            if (msg.message == "fftcomplete") {
                for (int i=0; i < 4; i++) {
                    val[i]=interp[i].lopass(fabs(data->mir.mfccCoeffs[i+1]), 0.1*fabs(data->mir.mfccCoeffs[i+1]));
                }
            }
        }
    }

}
