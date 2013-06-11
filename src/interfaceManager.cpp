

#include "interfaceManager.h"
#include "geomFunctions.h"

namespace EAVIGUI {

    vector<InterfaceObject*> InterfaceManager::intObjs;
    vector<InterfaceObject*> InterfaceManager::panels;
    InterfaceObject* InterfaceManager::draggingTarget = NULL;
    InterfaceObject* InterfaceManager::touchingObject = NULL;
    interfaceObjectVector InterfaceManager::currentModalGroup = NULL;
    touchListenerProxy InterfaceManager::touchListener;
    eventProxy InterfaceManager::eventListener;
    map<string, ofTrueTypeFont> InterfaceManager::fontList;
    float InterfaceManager::deviceScaleMod = 1.0;
    bool InterfaceManager::redirectMouseToTouch = false;

    InterfaceObject* InterfaceManager::addObject(InterfaceObject* obj) {
        intObjs.push_back(obj);
        return intObjs.back();
    }

    void InterfaceManager::addObjects(InterfaceObjectGroup objs) {
        for(int i=0; i < objs.size(); i++)
            intObjs.push_back(objs[i]);
    }

    InterfaceObject* InterfaceManager::lastObject() {
        return intObjs.back();
    }

    InterfaceObject* InterfaceManager::addPanel(InterfaceObject* obj) {
        panels.push_back(obj);
        return panels.back();
    }

    void InterfaceManager::setup() {
        ofAddListener(ofEvents().update, &eventListener, &eventProxy::update);
        ofAddListener(ofEvents().draw, &eventListener, &eventProxy::draw);
#ifndef TARGET_OF_IPHONE        
        ofAddListener(ofEvents().mousePressed, &eventListener, &eventProxy::mousePressed);
        ofAddListener(ofEvents().mouseReleased, &eventListener, &eventProxy::mouseReleased);
        ofAddListener(ofEvents().mouseDragged, &eventListener, &eventProxy::mouseDragged);
        ofAddListener(ofEvents().mouseMoved, &eventListener, &eventProxy::mouseMoved);
    //    ofAddListener(ofEvents().exit, this, &InterfaceManager::exit);
#endif        
        for(int i=0; i < intObjs.size(); i++) {
            intObjs[i]->setup();
        }
        for(int i=0; i < panels.size(); i++) {
            panels[i]->setup();
        }
        touchListener.setup();
    }

    void InterfaceManager::draw() {
        for(int i=0; i < intObjs.size(); i++) {
            if (intObjs[i]->getParent() == NULL) {
                intObjs[i]->draw();
            }
        }	
        for(int i=0; i < panels.size(); i++) {
            if (panels[i]->isVisible()) {
                ofSetColor(200,200,200,200);
                ofFill();
                ofRect(0, 0, ofGetWidth(), ofGetHeight());
                panels[i]->draw();
                break;
            }
        }
    }

    vector<InterfaceObject*>* InterfaceManager::getLiveObjectList() {
        interfaceObjectVector liveObjectList;
        liveObjectList = &intObjs;
        
        if (currentModalGroup != NULL) {
            liveObjectList = currentModalGroup;
        }
        return liveObjectList;
    }
    
    ofTouchEventArgs createTouch(int x, int y) {
        ofTouchEventArgs touch;
        touch.x = x;
        touch.y = y; 
        touch.numTouches = 1;
        touch.id=0;
        return touch;
    }
        

    void InterfaceManager::mouseMoved(int x, int y) {
        
        
        static InterfaceObject* mouseOverObject = NULL;
        
        interfaceObjectVector liveObjectList = InterfaceManager::getLiveObjectList();
        bool found = false;
        int i = liveObjectList->size();
        while(i--) {
            if (liveObjectList->at(i)->isInteractive() && geom::pointInRect(x,y,liveObjectList->at(i)->x, liveObjectList->at(i)->y, liveObjectList->at(i)->getWidth(), liveObjectList->at(i)->getHeight())) {
                found = true;
                if ((mouseOverObject != liveObjectList->at(i)) && (mouseOverObject != NULL)) {
                    mouseOverObject->mouseExit();
                }
                mouseOverObject = liveObjectList->at(i);
                liveObjectList->at(i)->mouseMoved(x - liveObjectList->at(i)->x, y - liveObjectList->at(i)->y);
                break;
            }
        }
        if (!found && (mouseOverObject != NULL)) {
            mouseOverObject->mouseExit();
            mouseOverObject = NULL;
        }	
        
        
    }

    void InterfaceManager::mouseDragged(int x, int y, int button){
        if (redirectMouseToTouch) {
            ofTouchEventArgs touch = createTouch(x, y);
            InterfaceManager::touchDown(touch);
        }else{
            if (NULL == InterfaceManager::draggingTarget) {
                vector<InterfaceObject*>* liveObjectList = InterfaceManager::getLiveObjectList();
                int i = liveObjectList->size();
                while(i--) {
                    if (liveObjectList->at(i)->isInteractive() && geom::pointInRect(x,y,liveObjectList->at(i)->x, liveObjectList->at(i)->y, liveObjectList->at(i)->getWidth(), liveObjectList->at(i)->getHeight())) {
                        //liveObjectList->at(i)->mouseDragged(x - liveObjectList->at(i)->x, y - liveObjectList->at(i)->y, button);
                        InterfaceManager::draggingTarget = liveObjectList->at(i);
                        break;
                    }
                }
            }
            if (NULL != InterfaceManager::draggingTarget) {
                InterfaceManager::draggingTarget->mouseDragged(x - InterfaceManager::draggingTarget->x, y - InterfaceManager::draggingTarget->y, button);
            }
        }
    }

    void InterfaceManager::mousePressed(int x, int y, int button){
        if (redirectMouseToTouch) {
            ofTouchEventArgs touch = createTouch(x, y);
            InterfaceManager::touchDown(touch);
        }else{
        
            vector<InterfaceObject*>* liveObjectList = InterfaceManager::getLiveObjectList();
            int i = liveObjectList->size();
            while(i--) {
                if (liveObjectList->at(i)->isInteractive() && geom::pointInRect(x,y,liveObjectList->at(i)->x, liveObjectList->at(i)->y, liveObjectList->at(i)->getWidth(), liveObjectList->at(i)->getHeight())) {
                    liveObjectList->at(i)->mousePressed(x - liveObjectList->at(i)->x, y - liveObjectList->at(i)->y, button);
                    break;
                }
            }
        }
    }

    void InterfaceManager::mouseReleased(int x, int y, int button){
        if (redirectMouseToTouch) {
            ofTouchEventArgs touch = createTouch(x, y);
            InterfaceManager::touchUp(touch);
        }else{

            if (NULL != InterfaceManager::draggingTarget) {
                InterfaceManager::draggingTarget->mouseReleased(x - InterfaceManager::draggingTarget->x, y - InterfaceManager::draggingTarget->y, button);
                InterfaceManager::draggingTarget = NULL;
            }else{
                vector<InterfaceObject*>* liveObjectList = InterfaceManager::getLiveObjectList();
                int i = liveObjectList->size();
                while(i--) {
                    if (liveObjectList->at(i)->isInteractive() && geom::pointInRect(x,y,liveObjectList->at(i)->x, liveObjectList->at(i)->y, liveObjectList->at(i)->getWidth(), liveObjectList->at(i)->getHeight())) {
                        liveObjectList->at(i)->mouseReleased(x - liveObjectList->at(i)->x, y - liveObjectList->at(i)->y, button);
                        break;
                    }
                }
            }
        }
        
    }

    InterfaceObject* InterfaceManager::getTargetObject(ofTouchEventArgs &touch) {
    //	cout << "testing " << touch.x << ", " << touch.y << endl;
        InterfaceObject *target = NULL;
        interfaceObjectVector liveObjectList = InterfaceManager::getLiveObjectList();
        int i = liveObjectList->size();
        while(i--) {
            ofRectangle rotatedRect = liveObjectList->at(i)->getRectWithRotation();
            if (liveObjectList->at(i)->isInteractive() && liveObjectList->at(i)->isVisible() &&
                geom::pointInRect(touch.x,touch.y,rotatedRect.x, rotatedRect.y, rotatedRect.width, rotatedRect.height)) {
//                cout << touch.x << ", " << touch.y << ", " << rotatedRect.x << ", " << rotatedRect.y << ", " << rotatedRect.width << ", " << rotatedRect.height << endl;
                //convert from screen coordinate system to object coordinate system
                ofTouchEventArgs tempTouch = touch;
                liveObjectList->at(i)->transformTouchForRotation(tempTouch);
                if(liveObjectList->at(i)->canInteractAt(tempTouch.x, tempTouch.y)) {
                    target = liveObjectList->at(i);
                    touch = tempTouch;
                    //cout << "found" << endl;
                    break;
                }
            }
        }
        return target;
    }


    void InterfaceManager::touchDown(ofTouchEventArgs &touch) {
        //cout << "Touch down " << touch.x << "," << touch.y << endl;
        InterfaceObject *obj = InterfaceManager::getTargetObject(touch);
        if (NULL != obj) {
            //cout << "touch down: " << obj->id << endl;
            InterfaceManager::touchingObject = obj;
            obj->touchDown(touch);
        }
        
    }

    void InterfaceManager::touchMoved(ofTouchEventArgs &touch) {
        //cout << "Touch moved\n";
        InterfaceObject *obj = InterfaceManager::getTargetObject(touch);
        if (NULL != obj) {
            //cout << "Touch moved: " << obj->id << endl;
            if (InterfaceManager::touchingObject != NULL && InterfaceManager::touchingObject != obj) {
                //cout << "Touch exit: " << touchingObject->id << endl;
                InterfaceManager::touchingObject->touchExit();
            }
            InterfaceManager::touchingObject = obj;
            obj->touchMoved(touch);
        }else{
            if (InterfaceManager::touchingObject != NULL) {
                //cout << "Touch exit null: " << touchingObject->id << endl;
                InterfaceManager::touchingObject->touchExit();
            }
            InterfaceManager::touchingObject = NULL;
        }
    }

    void InterfaceManager::touchUp(ofTouchEventArgs &touch) {
        //cout << "Touch up " << touch.x << "," << touch.y << endl;
        InterfaceObject *obj = InterfaceManager::touchingObject;
        if (NULL == obj) 
            obj = InterfaceManager::getTargetObject(touch);
        else {
            obj->transformTouchForRotation(touch);
        }
        if (NULL != obj) {
            //cout << "touch up: " << obj->id << endl;
            InterfaceManager::touchingObject = NULL;
            obj->touchUp(touch);
        }
    }


    void InterfaceManager::touchDoubleTap(ofTouchEventArgs &touch) {
        InterfaceObject *obj = InterfaceManager::getTargetObject(touch);
        if (NULL != obj) {
            obj->touchDoubleTap(touch);
        }
        
    }

    void InterfaceManager::touchCancelled(ofTouchEventArgs &touch) {
        
    }


    void InterfaceManager::showHideModalGroup(InterfaceObjectGroup *modalGroup, bool visible) {
        if (NULL != InterfaceManager::touchingObject) {
            InterfaceManager::touchingObject->touchExit();
            InterfaceManager::touchingObject = NULL;
        }
        for(int i=0; i < modalGroup->size(); i++) {
            modalGroup->at(i)->setVisible(visible);
        }
        currentModalGroup = visible ? modalGroup : NULL;
    }

    void InterfaceManager::update() {
        for (int i=0; i < intObjs.size(); i++) {
            intObjs[i]->update();
        }
    }

    InterfaceObject* InterfaceManager::beingTouched() {
        return InterfaceManager::touchingObject;
    }

    void InterfaceManager::addFont(string identifier, string fontname, int size) {
        InterfaceManager::fontList[identifier] = ofTrueTypeFont();
        InterfaceManager::fontList[identifier].loadFont(fontname, size);
    }
    
    
    void InterfaceManager::setGroupVisibility(InterfaceObjectGroup &objects, bool visibility) {
        for(int i=0; i < objects.size(); i++) {
            objects[i]->setVisible(visibility);
        }
    }
    
    ///////////////////////////////////////////////////////////
    
    void touchListenerProxy::setup() {
        ofRegisterTouchEvents(this);
    };

    void touchListenerProxy::touchDown(ofTouchEventArgs &touch) {
        InterfaceManager::touchDown(touch);
    }
    void touchListenerProxy::touchMoved(ofTouchEventArgs &touch) {
        InterfaceManager::touchMoved(touch);
    }
    void touchListenerProxy::touchUp(ofTouchEventArgs &touch) {
        InterfaceManager::touchUp(touch);
    }
    void touchListenerProxy::touchDoubleTap(ofTouchEventArgs &touch) {
        InterfaceManager::touchDoubleTap(touch);
    }

    void touchListenerProxy::touchCancelled(ofTouchEventArgs &touch) {
        
    }


    void eventProxy::draw(ofEventArgs &data) {
        InterfaceManager::draw();
    }

    void eventProxy::update(ofEventArgs &data) {
        InterfaceManager::update();
    }
    
    void eventProxy::mousePressed(ofMouseEventArgs &args) {
        InterfaceManager::mousePressed(args.x, args.y, args.button);
    }

    void eventProxy::mouseReleased(ofMouseEventArgs &args) {
        InterfaceManager::mouseReleased(args.x, args.y, args.button);
    }
    
    void eventProxy::mouseDragged(ofMouseEventArgs &args) {
        InterfaceManager::mouseDragged(args.x, args.y, args.button);
    }
    
    void eventProxy::mouseMoved(ofMouseEventArgs &args) {
        InterfaceManager::mouseMoved(args.x, args.y);
    }
    

};