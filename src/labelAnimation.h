//
//  labelAnimation.h
//  DRSAppOSX
//
//  Created by Chris Kiefer on 29/08/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#ifndef DRSAppOSX_labelAnimation_h
#define DRSAppOSX_labelAnimation_h

#include "label.h"

namespace EAVIGUI {
    
    class LabelAnimation : public Label {
    public:
        LabelAnimation(InterfaceListener *_listener, int _id, int _x, int _y, int _w, int _h, ofTrueTypeFont *_font, string _text, ofColor _colour):
        Label(_listener, _id, _x, _y, _w, _h, _font, _text, _colour) {}

    protected:
        void drawToBuffer();
    };
    
};


#endif
