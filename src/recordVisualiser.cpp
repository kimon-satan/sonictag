//
//  recordVisualiser.cpp
//  SonicTag3
//
//  Created by Chris on 20/06/2013.
//
//

#include "recordVisualiser.h"

namespace EAVIGUI {
    
    RecordVisualiser::RecordVisualiser(InterfaceListener *_listener, int _id, int _x, int _y, int _w, int _h, sharedDataContainer *_data) : InterfaceObject(_listener, _id, _x, _y)
    {
        data = _data;
        setWidth(_w);
        setHeight(_h);
        setIsInteractive(true);
        on = false;
        cx = w / 2.0;
        cy = h / 2.0;
        markerAngle = 0;
        radius = w / 4.0;
        amp = 1;
    }

    void RecordVisualiser::setAmp(float val) {
        amp = val;
        invalidate();
    }
    void RecordVisualiser::setRecording(bool val) {
        on = val;
        invalidate();
    }

    
    void RecordVisualiser::update() {
    }
    
    void RecordVisualiser::drawToBuffer() {
        ofEnableSmoothing();
        ofSetCircleResolution(200);
        ofBackground(255,255,255);
        ofFill();
        if (on) {
            ofSetColor(200,0,0);
        }else{
            ofSetColor(0,0,0);
        }
        if (on)
            markerAngle += 0.03;
        ofCircle(cx, cy, radius * amp);
        ofSetColor(255,255,255);
        ofCircle(cx, cy, 0.7 * radius * amp);
        float markerWidth = 0.5;
        float tradius = radius * 1.2 * amp;
        ofTriangle(cx, cy, cx + (cos(markerAngle) * tradius), cy + (sin(markerAngle) * tradius),
                   cx + (cos(markerAngle + markerWidth) * tradius), cy + (sin(markerAngle + markerWidth) * tradius));
    }
        
}
