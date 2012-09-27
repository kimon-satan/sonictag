//
//  imageButton.cpp
//  sonicTag2
//
//  Created by Chris Kiefer on 25/07/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#include <iostream>
#include "imageButton.h"

namespace EAVIGUI {
    
    ImageButton::ImageButton(InterfaceListener *_listener, int _id, int _x, int _y, string imageFileName) : InterfaceObject(_listener, _id, _x, _y) {
        im.loadImage(imageFileName);
        init();
    }
    
    ImageButton::ImageButton(InterfaceListener *_listener, int _id, int _x, int _y, ofImage _im) : InterfaceObject(_listener, _id, _x, _y) {
        im = _im;
        init();
    }
    
    void ImageButton::init() {
        setWidth(im.width);
        setHeight(im.height);
        setIsInteractive(true);
        imColor = ofColor(255,255,255);
    }
    
    void ImageButton::loadNewImage(string imageFileName) {
        im.loadImage(imageFileName);
        init();
        invalidate();
    }

 
    void ImageButton::drawToBuffer() {
        ofSetColor(imColor);
        im.draw(0,0,w,h);
    }
    
}
