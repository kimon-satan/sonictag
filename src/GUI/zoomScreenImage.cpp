//
//  zoomScreenImage.cpp
//  DRSAppIOS
//
//  Created by Chris Kiefer on 29/08/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#include <iostream>
#include "zoomScreenImage.h"


namespace EAVIGUI {
    
    ZoomScreenImage::ZoomScreenImage(InterfaceListener *_listener, int _id, int _x, int _y, ofImage *_im) : InterfaceObject(_listener, _id, _x, _y) {
        im = _im;
        init();
        setDeviceScaling(false);        
        setDims(ofGetWidth(), ofGetHeight());
        setRotationAroundCenter();
    }
    
    void ZoomScreenImage::updateImage(ofImage *_im) {
        im = _im;
    }

    void ZoomScreenImage::init() {
        setIsInteractive(false);
    }
    
    void ZoomScreenImage::setDims(int nw, int nh) {
         float widthHeightRatio = im->width / (float) im->height;
        setHeight(nh);
        imHeight = nh;
        imWidth = nh * widthHeightRatio;
        imY = (h - imHeight) / 2.0;
        imX = (nw - imWidth) / 2.0;
        setWidth(imWidth);
    }
    
    void ZoomScreenImage::drawToBuffer() {
        ofSetColor(255);
        im->draw(imX, imY, imWidth, imHeight);
    }
    
    void ZoomScreenImage::touchUp(ofTouchEventArgs &touch) {
    }
    
    void ZoomScreenImage::deviceOrientationChanged(int newOrientation) {
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
    
    
    
}
