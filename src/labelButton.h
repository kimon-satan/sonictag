/*
 *  labelButton.h
 *  EchoFoamLiveLink
 *
 *  Created by chris on 01/07/2010.
 *  Copyright 2010 Phalanger. All rights reserved.
 *
 */

#ifndef _LABEL_BUTTON_H
#define _LABEL_BUTTON_H


#include "interfaceObject.h"
#include <iostream>
#include "ofmain.h"

namespace EAVIGUI {

    enum labelButtonEvents {
        CLICKED
    };


    class LabelButton : public InterfaceObject {
    public:
        
        LabelButton(InterfaceListener *_listener, int _id, int _x, int _y, ofTrueTypeFont *_font, string _text, 
                      int _defaultColour, int _mouseOverColour, int _mouseDownColour, int _disabledColour);
        void setText(string t);
        ofTrueTypeFont *font;
        ofColor colour;
        void setEnabled(bool val);
        
        void mouseMoved( int x, int y );
        void mouseExit();
        void mousePressed( int x, int y, int button );
        void mouseReleased(); 
        void mouseReleased(int x, int y, int button );
        void mouseDragged(int x, int y, int button);
        void touchDown(ofTouchEventArgs &touch);
        void touchMoved(ofTouchEventArgs &touch);
        void touchUp(ofTouchEventArgs &touch);
        void touchExit();

        
    protected:
        virtual void drawToBuffer();
        bool invalidated;
        string text;
        int defaultColour, mouseOverColour, mouseDownColour, disabledColour;
        bool disabled;
        

    };
    
};
#endif