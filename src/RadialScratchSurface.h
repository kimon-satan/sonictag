//
//  RadialScratchSurface.h
//  DRSApp
//
//  Created by Chris Kiefer on 01/08/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#ifndef DRSApp_RadialScratchSurface_h
#define DRSApp_RadialScratchSurface_h

#include "interfaceObject.h"
#include <iostream>

using namespace std;

namespace EAVIGUI {
    
    class RadialScratchSurface : public InterfaceObject {
    public:
        RadialScratchSurface(InterfaceListener *_listener, int _id, int _x, int _y, int _w, int _h);
        void touchDown(ofTouchEventArgs &touch);
        void touchMoved(ofTouchEventArgs &touch);
        void touchUp(ofTouchEventArgs &touch);
        void processTouch(ofTouchEventArgs &touch);
        float getVelocity(){return velocity;}
    protected:
        void drawToBuffer();
        bool showAngle;
        float touchX, touchY;
        float midX, midY;
        float velocity;
        ofFbo fbo1, fbo2;
        int fboD;
    };
    
};



#endif
