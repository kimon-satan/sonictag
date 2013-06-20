//
//  MfccVisualiser.h
//  SonicTag3
//
//  Created by Chris on 04/06/2013.
//
//

#ifndef __SonicTag3__MfccVisualiser__
#define __SonicTag3__MfccVisualiser__

#include <iostream>

#include "EAVIGUI.interfaceObject.h"
#include <iostream>
#include "sharedData.h"

using namespace std;

namespace EAVIGUI {
    
    class MfccVisualiser : public InterfaceObject {
    public:
        MfccVisualiser(InterfaceListener *_listener, int _id, int _x, int _y, int w, int h, sharedDataContainer *data);
        void gotMessage(ofMessage &msg);
    protected:
        void init();
        void update();
        virtual void drawToBuffer();
        float radius, cx, cy, val[4], unit;
        ofxMaxiFilter interp[4];
        sharedDataContainer *data;
    };
    
};



#endif /* defined(__SonicTag3__MfccVisualiser__) */
