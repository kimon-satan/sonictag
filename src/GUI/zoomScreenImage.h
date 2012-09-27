//
//  zoomScreenImage.h
//  DRSAppIOS
//
//  Created by Chris Kiefer on 29/08/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#ifndef DRSAppIOS_zoomScreenImage_h
#define DRSAppIOS_zoomScreenImage_h


#include "interfaceObject.h"
#include <iostream>
#include "ofMain.h"

using namespace std;

namespace EAVIGUI {
    
    class ZoomScreenImage : public InterfaceObject {
    public:
        ZoomScreenImage(InterfaceListener *_listener, int _id, int _x, int _y, ofImage *im);
        ofImage* getImage() {return im;}
        void touchUp(ofTouchEventArgs &touch);
        ofPoint touchPoint, touchCoords;
        void deviceOrientationChanged(int newOrientation);
        void updateImage(ofImage *im);
    protected:
        void init();
        void setDims(int nw, int nh);
        virtual void drawToBuffer();
        ofImage *im;
        float imHeight, imWidth;
        int imY, imX;
    };
    
};

#endif
