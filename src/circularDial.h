//
//  circularDial.h
//  DRSApp
//
//  Created by Chris Kiefer on 31/07/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#ifndef DRSApp_circularDial_h
#define DRSApp_circularDial_h

#include "EAVIGUI.interfaceObject.h"
#include <iostream>

using namespace std;

namespace EAVIGUI {
    
    class CircularDial : public InterfaceObject {
    public:
        CircularDial(InterfaceListener *_listener, int _id, int _x, int _y, int _w, int _h);
        void setValue(float newValue);
        float getValue(){return value;}
        void touchDown(ofTouchEventArgs &touch);
        void touchMoved(ofTouchEventArgs &touch);
        void processTouch(ofTouchEventArgs &touch);

    protected:
        void drawToBuffer();
        float value;
    private:
        int divisions;
    };
    
};


#endif
