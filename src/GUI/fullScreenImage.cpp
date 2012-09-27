//
//  fullScreenImage.cpp
//  DRSAppOSX
//
//  Created by Chris Kiefer on 24/08/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#include <iostream>
#include "FullScreenImage.h"

namespace EAVIGUI {
    
    FullScreenImage::FullScreenImage(InterfaceListener *_listener, int _id, int _x, int _y, string imageFileName) : InterfaceObject(_listener, _id, _x, _y) {
        im.loadImage(imageFileName);
        init();
        setDeviceScaling(false);
        setDims(ofGetWidth(), ofGetHeight());
        setRotationAroundCenter();
    }
    
    void FullScreenImage::init() {
        setIsInteractive(true);
    }
    
    void FullScreenImage::setDims(int nw, int nh) {
        setWidth(nw);
        float widthHeightRatio = im.height / (float) im.width;
        imHeight = nw * widthHeightRatio;
        imWidth = nw;
        setHeight(nh);
        imY = (h - imHeight) / 2.0;
    }

    void FullScreenImage::drawToBuffer() {
        ofSetColor(255);
        im.draw(0, imY, w, imHeight);
    }
    
    void FullScreenImage::touchUp(ofTouchEventArgs &touch) {
        touchPoint.x = MAX(0,MIN(touch.x * ((float) im.width / imWidth), im.width));
        touchPoint.y = MAX(0, MIN((touch.y - imY) * ((float) im.height / imHeight), im.height));
        touchCoords.x = touch.x;
        touchCoords.y = touch.y;
        cout << touchPoint.x << ", " << touchPoint.y << endl;
        InterfaceObject::touchUp(touch);
    }
    
    void FullScreenImage::deviceOrientationChanged(int newOrientation) {
        if (newOrientation != 5 && newOrientation != 6) {
            if (newOrientation == 3 || newOrientation == 4) {
                setDims(ofGetHeight(), ofGetWidth());
                x = (ofGetWidth() / 2.0) - (ofGetHeight() / 2.0);
                y = (ofGetHeight() / 2.0) - (ofGetWidth() / 2.0);
            }else if (newOrientation == 1 || 2 == newOrientation) {
                setDims(ofGetWidth(), ofGetHeight());            
                x = 0;
                y = 0;
            }
            setRotationAroundCenter();
        }
        InterfaceObject::deviceOrientationChanged(newOrientation);
    }

    bool FullScreenImage::canInteractAt(int x, int y) {
//        cout << "CAI: " << x << ", " << y << ", " << (y > imY && y < (imY + imHeight)) << endl;
        return (y > imY + (imHeight * 0.2) && y < (imY + (imHeight * 0.95))) ;
    }


    
}
