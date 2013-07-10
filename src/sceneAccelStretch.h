//
//  sceneAccelStretch.h
//  sonicTag2
//
//  Created by Chris Kiefer on 06/07/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#ifndef sonicTag2_sceneAccelStretch_h
#define sonicTag2_sceneAccelStretch_h

#include "sceneFingerStretch.h"
#include "EAIT.h"

class sceneAccelStretch : public sceneFingerStretch {
public:
    void setup(sharedDataContainer *data);        
    void update();
    void draw();
    float getNextSample();
    string getTitle() {return string("Motion Time\nStretch")
        .append(motionTriggering ?
                string("\n(").append((threshType == THRESHLOW ? "low" : "high")).append(" trig)")
                :
                "");
    }
    void setMotionTriggering(bool newVal);
    void touchDown(ofTouchEventArgs &touch);
	void touchMoved(ofTouchEventArgs &touch);
	void touchUp(ofTouchEventArgs &touch);
	void touchDoubleTap(ofTouchEventArgs &touch);
    void beginScene();
//    void setThreshold(float thresh);
    enum thresholdtypes {THRESHLOW, THRESHHIGH};
    void setThreshold(thresholdtypes t);
    
protected:
    bool motionTriggering;
    float lastX, lastY, lastZ;
    float rateVal, pitchVal;
    EAIT::MovingAverageF accelTotalMA, ampMA, pitchMA;
    EAIT::BasicTriggerF motionTrig;
    float motionThresh;
    float sensitivity, senseMin, senseMax;
    thresholdtypes threshType;
    

};

#endif
