//
//  labelAnimation.cpp
//  DRSAppOSX
//
//  Created by Chris Kiefer on 29/08/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#include <iostream>
#include "labelAnimation.h"


namespace EAVIGUI {
    void LabelAnimation::drawToBuffer() {
        ofFill();
        ofSetColor(backgroundColour);
        ofRect(0,0, w, h);
        ofSetColor(colour);
        ofScale(ofRandom(0.95,1.05), ofRandom(0.95, 1.05));
        ofRotate(ofRandom(0, 0.01));
        font->drawString(text, 0 + ofRandom(10), font->getLineHeight() + ofRandom(-10, 10));
        invalidate();
    }

}