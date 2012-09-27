//
//  HeadVisualiser.cpp
//  DRSApp
//
//  Created by Chris Kiefer on 31/07/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#include <iostream>
#include "HeadVisualiser.h"

namespace EAVIGUI {
    
    HeadVisualiser::HeadVisualiser(InterfaceListener *_listener, int _id, int _x, int _y) : InterfaceObject(_listener, _id, _x, _y) {
        init();
    }
    
    void HeadVisualiser::init() {
        im = NULL;
        setWidth(0);
        setHeight(0);
        setIsInteractive(false);
    }
    
    void HeadVisualiser::setImage(ofImage *newIm) {
        im = newIm;
        setWidth(im->width);
        setHeight(im->height);
        invalidate();
    }

    
    void HeadVisualiser::drawToBuffer() {
        if (NULL != im) {
            ofSetColor(255,255,255);
            im->draw(0,0,w,h);
        }
    }
    
}
