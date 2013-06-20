//
//  recordVisualiser.h
//  SonicTag3
//
//  Created by Chris on 20/06/2013.
//
//

#ifndef __SonicTag3__recordVisualiser__
#define __SonicTag3__recordVisualiser__

#include <iostream>

#include "EAVIGUI.interfaceObject.h"
#include <iostream>
#include "sharedData.h"

using namespace std;

namespace EAVIGUI {
    
    class RecordVisualiser : public InterfaceObject {
    public:
        RecordVisualiser(InterfaceListener *_listener, int _id, int _x, int _y, int w, int h, sharedDataContainer *data);
        void setAmp(float val);
        void setRecording(bool val);
    protected:
        void update();
        void drawToBuffer();
        sharedDataContainer *data;
        float amp;
        float on;
        float cx, cy;
        float markerAngle;
        float radius;
    };
    
};

#endif /* defined(__SonicTag3__recordVisualiser__) */
