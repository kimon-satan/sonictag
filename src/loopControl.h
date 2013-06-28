//
//  loopControl.h
//  SonicTag3
//
//  Created by Chris on 28/06/2013.
//
//

#ifndef __SonicTag3__loopControl__
#define __SonicTag3__loopControl__

#include "EAVIGUI.interfaceObject.h"
#include <iostream>
#include "sharedData.h"
#include "baseScene.h"

using namespace std;

namespace EAVIGUI {
    
    class LoopControl : public InterfaceObject {
    public:
        LoopControl(InterfaceListener *_listener, int _id, int _x, int _y, int w, int h, sharedDataContainer *data);
        void touchDown(ofTouchEventArgs &touch);
        void touchMoved(ofTouchEventArgs &touch);
        void touchUp(ofTouchEventArgs &touch);
        float start, end;
    protected:
        void drawToBuffer();
        sharedDataContainer *data;
        ofPoint caretPos;
        void moveCaret(ofTouchEventArgs &touch);
    };
    
};

#endif /* defined(__SonicTag3__loopControl__) */
