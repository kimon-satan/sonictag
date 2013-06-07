//
//  fullScreenImage.h
//  DRSAppOSX
//
//  Created by Chris Kiefer on 24/08/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#ifndef DRSAppOSX_fullScreenImage_h
#define DRSAppOSX_fullScreenImage_h

#include "interfaceObject.h"
#include <iostream>
#include "ofMain.h"

using namespace std;

namespace EAVIGUI {
    
    class FullScreenImage : public InterfaceObject {
    public:
        FullScreenImage(InterfaceListener *_listener, int _id, int _x, int _y, string imageFileName);
        ofImage getImage() {return im;}
        void touchUp(ofTouchEventArgs &touch);
        ofPoint touchPoint, touchCoords;
        void deviceOrientationChanged(int newOrientation);
        bool canInteractAt(int x, int y);
    protected:
        void init();
        void setDims(int nw, int nh);
        virtual void drawToBuffer();
        ofImage im;
        float imHeight, imWidth;
        int imY;
    };
    
};


#endif
