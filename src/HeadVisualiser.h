//
//  HeadVisualiser.h
//  DRSApp
//
//  Created by Chris Kiefer on 31/07/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#ifndef DRSApp_HeadVisualiser_h
#define DRSApp_HeadVisualiser_h

#include "interfaceObject.h"
#include <iostream>

using namespace std;

namespace EAVIGUI {
    
    class HeadVisualiser : public InterfaceObject {
    public:
        HeadVisualiser(InterfaceListener *_listener, int _id, int _x, int _y);
        void setImage(ofImage *newIm);
    protected:
        void init();
        virtual void drawToBuffer();
        ofImage *im;
    };
    
};


#endif
