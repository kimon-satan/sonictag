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
        void updateWaveform(maxiSample *sample);
        void beginScene();
        void setPos(float newPos);
        void reset();
    protected:
        void drawToBuffer();
        sharedDataContainer *data;
        ofVec2f caretPos;
        void moveCaret(ofTouchEventArgs &touch);
        ofFbo waveFBO;
        int fboWidth, fboHeight;
        float minCaretDist, maxCaretDist, caretDistRange;
        float playHeadPos;
        
    };
    
};

#endif /* defined(__SonicTag3__loopControl__) */
