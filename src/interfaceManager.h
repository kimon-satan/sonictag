/*
 *  interfaceManager.h
 *  EchoFoamLiveLink
 *
 *  Created by chris on 01/07/2010.
 *  Copyright 2010 Phalanger. All rights reserved.
 *
 */

#ifndef _INTERFACE_MANAGER_H
#define _INTERFACE_MANAGER_H

#include "ofMain.h"
#include "interfaceObject.h"
#include "label.h"
#include "labelButton.h"
#include "imageButton.h"
#include "fullScreenImage.h"
#include <map>

namespace EAVIGUI {

    typedef vector<InterfaceObject*> InterfaceObjectGroup;
    typedef vector<InterfaceObject*>* interfaceObjectVector;

    class touchListenerProxy;
    class eventProxy;

    class InterfaceManager {
    public:
        
        static InterfaceObject* addObject(InterfaceObject* obj);
        static void addObjects(InterfaceObjectGroup objs);        
        static InterfaceObject* addPanel(InterfaceObject* obj);
        static InterfaceObject* lastObject();
        static void setup();
        static void draw();
        static void update();
        static void mouseMoved(int x, int y);
        static void mouseDragged(int x, int y, int button);
        static void mousePressed(int x, int y, int button);
        static void mouseReleased(int x, int y, int button);
        static void touchDown(ofTouchEventArgs &touch);
        static void touchMoved(ofTouchEventArgs &touch);
        static void touchUp(ofTouchEventArgs &touch);
        static void touchDoubleTap(ofTouchEventArgs &touch);
        static void touchCancelled(ofTouchEventArgs &touch);
        
        static void showHideModalGroup(InterfaceObjectGroup *modalGroup, bool visible);
        static bool modalShowing() {return currentModalGroup != NULL;}
        
        static InterfaceObject *beingTouched();
        static touchListenerProxy touchListener;
        static eventProxy eventListener;
        
        static map<string, ofTrueTypeFont> fontList;
        static void addFont(string identifier, string fontname, int size);
        
        static void setGroupVisibility(InterfaceObjectGroup &objects, bool visibility);
        static float deviceScaleMod;
        
        static bool redirectMouseToTouch;

    private:
        static InterfaceObjectGroup intObjs;
        static InterfaceObjectGroup panels;
        static interfaceObjectVector getLiveObjectList();
        static InterfaceObject* draggingTarget;
        static InterfaceObject* getTargetObject(ofTouchEventArgs &touch);
        static InterfaceObject* touchingObject;
        static interfaceObjectVector currentModalGroup;


        
    };

    class touchListenerProxy {
    public:
        void setup();
        void touchDown(ofTouchEventArgs &touch);
        void touchMoved(ofTouchEventArgs &touch);
        void touchUp(ofTouchEventArgs &touch);
        void touchDoubleTap(ofTouchEventArgs &touch);
        void touchCancelled(ofTouchEventArgs &touch);
    };

    class eventProxy {
    public:
        void draw(ofEventArgs &data);
        void update(ofEventArgs &data);
        void mousePressed(ofMouseEventArgs &args);
        void mouseReleased(ofMouseEventArgs &args);
        void mouseDragged(ofMouseEventArgs &args);
        void mouseMoved(ofMouseEventArgs &args);
    };
    

};

#endif