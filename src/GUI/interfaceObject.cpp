#include "interfaceObject.h"
#include "interfaceManager.h"

//#define GUIDEGBUG

namespace EAVIGUI {
    
    InterfaceObject::InterfaceObject(InterfaceListener *_listener, int _id, int _x, int _y) {
        init(_listener, _id, _x, _y);
    }
    
    InterfaceObject::InterfaceObject(InterfaceListener *_listener, int _id, int _x, int _y, int _w, int _h) {
        init(_listener, _id, _x, _y);
        setWidth(_w);
        setHeight(_h);
    }
    
    void InterfaceObject::init(InterfaceListener *_listener, int _id, int _x, int _y) {
        tex = NULL;
        allocated = false;
        listener = _listener;
        id = _id;
        x = _x;
        y = _y;
        currentOrientation = ROT0;
        setWidth(0);
        setHeight(0);
        invalidated = false;
        alpha = red = green = blue = 255;
        visible = false;
        mouseState = SOMEWHERELSE;
        parent = NULL;
        setIsInteractive(true);
        rotation = 0;
        rotMode = ROTMODE_NONE;
        rotPt0.x = x;
        rotPt0.y = y;
        fadeTime = 300;
        fadeInTimeStamp = -1;
        fadeOutTimeStamp = -1;
        deviceScalingOn = true;
        setScale(1.0);
        setAnchorPoint(0.5, 0.5);
        calcScaleMods();
        pulsate = false;
        pulsateSpeed = 0.007;
        pulsateMin = 0.5;
        pulsateMax = 1.0;
    }
    
    InterfaceObject::~InterfaceObject() {
        if (NULL != tex)
            delete tex;
    }
    
    
    void InterfaceObject::setup() {
#ifdef TARGET_OF_IPHONE
        ofxiPhoneAlerts.addListener(this);
#endif
    }
    
    void InterfaceObject::allocateFBO() {
        ofFbo::Settings settings;
#ifdef TARGET_OPENGLES
        settings.width			= ofNextPow2(w);
        settings.height			= ofNextPow2(h);
#else
        settings.width			= w;
        settings.height			= h;
#endif
        fboWidth = settings.width;
        fboHeight = settings.height;
        settings.useDepth		= false;
        settings.useStencil		= false;
        tex = new ofFbo();
        tex->allocate(settings);
        allocated = true;
        invalidated = true;
    }
    
    void InterfaceObject::deallocateFBO() {
        allocated = false;
        delete tex;
    }
    
    void InterfaceObject::update(){	
    }
    
    void InterfaceObject::setScale(float newScale) {
        scale = newScale;
        totalScale = deviceScalingOn ? scale * InterfaceManager::deviceScaleMod : scale;
        calcScaleMods();
    }
    
    void InterfaceObject::setDeviceScaling(bool val) {
        deviceScalingOn = val;
        setScale(scale);
    }

    
    void InterfaceObject::setAnchorPoint(float ax, float ay) {
        anchorX = ax;
        anchorY = ay;
        calcScaleMods();
    }
    
    void InterfaceObject::getAnchorPoint(float &ax, float &ay) {
        ax = anchorX;
        ay = anchorY;
    }
    
    void InterfaceObject::drawToBuffer() {
        
    }
    
    void InterfaceObject::draw(){	
        if (visible) {
            if (invalidated) {
                invalidated = false;
                tex->begin();
                ofEnableAlphaBlending();
                ofClear(255);
                ofBackground(255,0);
                drawToBuffer();
                //                ofClearAlpha();
                tex->end();
                postDrawToBuffer();
            }
            
            int fadeAlpha = alpha;
            if (fadeInTimeStamp != -1) {
                int elapsed = ofGetElapsedTimeMillis() - fadeInTimeStamp;
                if (elapsed > fadeTime) {
                    fadeInTimeStamp = -1;
                }
                else {
                    fadeAlpha = round((float) elapsed / (float) fadeTime * (float) alpha);
                }
                
                
            }
            if (fadeOutTimeStamp != -1) {
                int elapsed = ofGetElapsedTimeMillis() - fadeOutTimeStamp;
                if (elapsed > fadeTime) {
                    fadeOutTimeStamp = -1;
                    hide();
                    fadeAlpha = 0;
                }
                else {
                    fadeAlpha = alpha - round((float) elapsed / (float) fadeTime * (float) alpha);
                }
                
            }
            if (visible) {
                float pulsateVal = (fabs(sin(ofGetElapsedTimeMillis() * pulsateSpeed)) * (pulsateMax - pulsateMin)) + pulsateMin;
                ofSetColor(red, green, blue, pulsate ? fadeAlpha * pulsateVal : fadeAlpha);
                
                glPushMatrix();
                glTranslatef(x,y,0);
                glRotatef(rotation,0,0,1);
                glTranslatef(-x,-y,0);
                //                float xScaleMod = ((totalScale - 1.0) * -w) * anchorX;
                //                float yScaleMod = ((totalScale - 1.0) * -h)  * anchorY;
                tex->draw(x + xScaleMod, y + yScaleMod, fboWidth * totalScale, fboHeight *totalScale);
                
#ifdef GUIDEGBUG
                ofNoFill();
                ofSetColor(255,0,0,255);
                ofRect(x + xScaleMod, y + yScaleMod, fboWidth * totalScale, fboHeight *totalScale);
                ofSetColor(100,100,100,255);
                ofRect(x + xScaleMod, y + yScaleMod, w * totalScale, h *totalScale);
#endif            
                glPopMatrix();
                
                for(int i=0; i < children.size(); i++) {
                    children[i]->draw();
                }
            }
        }
    }
    
    void InterfaceObject::postDrawToBuffer() {
        
    }
    
    bool InterfaceObject::canInteractAt(int x, int y) {
        return true;
    }


    
    void InterfaceObject::mouseMoved( int x, int y ){	
        mouseState = OVER;
        sendCallback(InterfaceObject::MOUSEMOVED);
    }
    
    void InterfaceObject::mouseExit() {	
        mouseState = SOMEWHERELSE;
    }
    
    void InterfaceObject::mousePressed( int x, int y, int button ){	
        mouseState = PRESSED;
        sendCallback(InterfaceObject::MOUSEPRESSED);
    }
    
    void InterfaceObject::mouseReleased(){	
        mouseState = OVER;
        sendCallback(InterfaceObject::MOUSERELEASED);
    }
    
    void InterfaceObject::mouseReleased(int x, int y, int button ){	
        mouseState = OVER;
        sendCallback(InterfaceObject::MOUSERELEASED);
    }
    
    
    void InterfaceObject::mouseDragged(int x, int y, int button) {
        mouseState = PRESSED;
        sendCallback(InterfaceObject::MOUSEDRAGGED);
    }
    
    void InterfaceObject::setEnabled(bool newEnabled) {	
    }
    
    InterfaceObject::InterfaceObject(){
        
    }
    
    void InterfaceObject::sendCallback(int eventTypeId) {
        listener->handleInterfaceEvent(id, eventTypeId, this);
    }
    
    void InterfaceObject::invalidate() {
        invalidated = true;
    }
    
    
    void InterfaceObject::addChild(InterfaceObject* child) {
        child->x += x;
        child->y += y;
        children.push_back(child);
        child->setParent(this);
        InterfaceManager::addObject(child);
    }
    
    bool InterfaceObject::hasChildren() {
        return (children.size() > 0);
    }
    
    void InterfaceObject::show() {
        if (!visible)
            allocateFBO();
        visible = true;
    }
    
    void InterfaceObject::hide() {
        if (visible)
            deallocateFBO();
        visible = false;
    }
    
    
    void InterfaceObject::setVisible(bool val, bool noFade) {
        if (!val) { //hiding
            mouseState = SOMEWHERELSE;
            if (noFade) 
                hide();
            else {
                fadeOutTimeStamp = ofGetElapsedTimeMillis();
                fadeInTimeStamp = -1;
            }
        }
        else { //showing
            show();
            if (!noFade) {
                fadeInTimeStamp = ofGetElapsedTimeMillis();
                fadeOutTimeStamp = -1;
            }
        }
    }
    
    bool InterfaceObject::isVisible() {
        return visible;
    }
    
    InterfaceObject* InterfaceObject::getParent() {
        return parent;
    }
    
    void InterfaceObject::setParent(InterfaceObject* newParent) {
        parent = newParent;
    }
    
    vector<InterfaceObject*>* InterfaceObject::getChildren() {
        return &children;
    }
    
    bool InterfaceObject::isInteractive() {
        return interactive;
    }
    
    void InterfaceObject::sendTouchCallback(int eventTypeId, ofTouchEventArgs &touch) {
        touchArgs = &touch;
        sendCallback(eventTypeId);
    }
    
    void InterfaceObject::touchDown(ofTouchEventArgs &touch) {
        sendTouchCallback(InterfaceObject::TOUCHDOWN, touch);
    }
    
    void InterfaceObject::touchDoubleTap(ofTouchEventArgs &touch) {
        sendTouchCallback(InterfaceObject::TOUCHDOUBLETAP, touch);
    }
    
    void InterfaceObject::touchMoved(ofTouchEventArgs &touch) {
        sendTouchCallback(InterfaceObject::TOUCHMOVED, touch);
    }
    
    void InterfaceObject::touchExit() {
    }
    
    void InterfaceObject::touchUp(ofTouchEventArgs &touch) {
        sendTouchCallback(InterfaceObject::TOUCHUP, touch);
    }
    
    
    
    
    void InterfaceObject::calcRotShifts() {
        xRotShift = (w/2.0) - (h / 2.0);
        yRotShift =  (h/2.0) - (w / 2.0);
    }
    void InterfaceObject::setWidth(int width){
        w = width; 
        if (allocated) {
            deallocateFBO();
            allocateFBO();
        }
//        calcRotShifts();
    }
    void InterfaceObject::setHeight(int height){
        h = height; 
        if (allocated) {
            deallocateFBO();
            allocateFBO();
        }
//        calcRotShifts();
    }
    
    int InterfaceObject::getWidth(){
        return w; 
    }
    
    int InterfaceObject::getHeight(){
        return h; 
    }
    
    int InterfaceObject::getScaledWidth(){
        return w * totalScale; 
    }
    
    int InterfaceObject::getScaledHeight(){
        return h * totalScale; 
    }
    
    void InterfaceObject::setRotation(rotations rot) {
        switch(rot) {
            case ROT0: rotation = 0; 
                xRotShift = 0;
                yRotShift = 0;
                break;
            case ROT90: rotation = 90; 
                xRotShift = h;
                yRotShift = 0;
                break;
            case ROT180: rotation = 180; 
                xRotShift = w;
                yRotShift = h;
                break;
            case ROT270: rotation = 270; 
                xRotShift = 0;
                yRotShift = w;
                break;
        };
        currentOrientation = rot;
    }
    
    void InterfaceObject::calcScaleMods() {
        xScaleMod = ((totalScale - 1.0) * -w) * anchorX;
        yScaleMod = ((totalScale - 1.0) * -h) * anchorY;                
    }
    
    
    ofRectangle InterfaceObject::getRectWithRotation() {
        ofRectangle res;
        switch(rotation) {
            case 0:
                res = ofRectangle(x + xScaleMod, y + yScaleMod, w * totalScale, h * totalScale);
                break;
            case 90:
                res = ofRectangle(x- (h * totalScale) - yScaleMod, y + xScaleMod, h * totalScale, w * totalScale);
                break;
            case 180:
                res = ofRectangle(x - (w * totalScale) - xScaleMod, y - (h * totalScale) - yScaleMod, w * totalScale, h * totalScale);
                break;
            case 270:
                res = ofRectangle(x + yScaleMod, y - (w * totalScale) - xScaleMod, h * totalScale, w * totalScale);
                break;
        }
        return res;
    }
    
    //    void InterfaceObject::updateRects() {
    //        
    //    }
    
    
    InterfaceObject* InterfaceObject::setRotationPoints(ofPoint r90, ofPoint r180, ofPoint r270) {
        rotPt90 = r90;
        rotPt180 = r180;
        rotPt270 = r270;
        rotMode = ROTMODE_SPECIFY;
        return this;
    }
    
    
    //convert from screen coordinate system to object coordinate system
    void InterfaceObject::transformTouchForRotation(ofTouchEventArgs &touch) {
        int tx = touch.x;
        int ty = touch.y;
        switch(rotation) {
            case 0: 
                touch.x -= x;
                touch.y -= y;
                break;
            case 90: 
                touch.x = ty - y;
                touch.y = x - tx;
                break;
            case 180: 
                touch.x = w - (touch.x - (x - w));
                touch.y = y - touch.y;
                break;
            case 270: 
                touch.x = y - ty;
                touch.y = tx - x;
                break;
        };
    }
    
    void InterfaceObject::deviceOrientationChanged(int newOrientation) {
        if (ROTMODE_NONE != rotMode) {
            switch (newOrientation) {
                case 1: //portrait
                    setRotation(ROT0);
                    break;
                case 2: // OFXIPHONE_ORIENTATION_UPSIDEDOWN
                    setRotation(ROT180);
                    break;
                case 4: //OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT 
                    setRotation(ROT270);
                    break;
                case 3: //OFXIPHONE_ORIENTATION_LANDSCAPE_LEFT
                    setRotation(ROT90);
            }
        }
        updatePosition();
    };
    
    void InterfaceObject::updatePosition() {
        switch (rotation) {
            case 0: //portrait
                x = rotPt0.x;
                y = rotPt0.y;
                break;
            case 180: // OFXIPHONE_ORIENTATION_UPSIDEDOWN
                x = rotPt180.x + xRotShift;
                y = rotPt180.y + yRotShift;
                break;
            case 270: //OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT 
                x = rotPt270.x + xRotShift;
                y = rotPt270.y + yRotShift;
                break;
            case 90: //OFXIPHONE_ORIENTATION_LANDSCAPE_LEFT
                x = rotPt90.x  + xRotShift;
                y = rotPt90.y + yRotShift;
                break;
        }
        invalidate();
    };
    
    ofPoint rotate(ofPoint n, float angle) {
        ofPoint m;
        m.x = ((n.x * cos(angle)) - (n.y*sin(angle)));
        m.y = ((n.x * sin(angle)) + (n.y*cos(angle)));	
        return m;
    }
    
    InterfaceObject* InterfaceObject::setRotationAroundCenter() {
        rotMode = ROTMODE_ROTATE;
        int cx = ofGetScreenWidth() / 2 ;
        int cy = ofGetScreenHeight() / 2 ;
        ofPoint z;
        z.x = x - cx;
        z.y = cy - y;
        ofPoint r;
        r= rotate(z, -PI/2);
        rotPt90.x =  r.x + cx - h;
        rotPt90.y = cy - r.y;
        r= rotate(z, PI);
        rotPt180.x =  r.x + cx - w;
        rotPt180.y = cy - r.y - h;
        r= rotate(z, PI/2);
        rotPt270.x =  r.x + cx;
        rotPt270.y = cy - r.y - w;
        setRotation(currentOrientation);
        updatePosition();        
        return this;
    }
    
    InterfaceObject* InterfaceObject::setRelativePositioning(float xpos, float ypos) {
        rotMode = ROTMODE_ROTATE;
        rotPt0.x = xpos * (float) ofGetWidth();
        rotPt0.y = ypos * (float) ofGetHeight();
        rotPt90.x =  ofGetWidth() - (ypos * (float) ofGetWidth()) - h;
        rotPt90.y = xpos * (float) ofGetHeight();
        rotPt180.x =  ofGetWidth() - (xpos * (float) ofGetWidth()) - w;
        rotPt180.y = ofGetHeight() - (ypos * (float) ofGetHeight()) - h;
        rotPt270.x =  (ypos * (float) ofGetWidth());
        rotPt270.y = ofGetHeight() - (xpos * (float) ofGetHeight()) - w;
        setRotation(currentOrientation);
        updatePosition();
        return this;
        
    }
    
    InterfaceObject* InterfaceObject::setRelativePositioning(float xpos, int xPixelOffset, float ypos, int yPixelOffset)
    {
        rotMode = ROTMODE_ROTATE;
        rotPt0.x = (xpos * (float) ofGetWidth()) + xPixelOffset;
        rotPt0.y = (ypos * (float) ofGetHeight()) + yPixelOffset;
        rotPt90.x =  ofGetWidth() - ((ypos * (float) ofGetWidth()) + yPixelOffset) - h;
        rotPt90.y = (xpos * (float) ofGetHeight()) + xPixelOffset;
        rotPt180.x =  ofGetWidth() - ((xpos * (float) ofGetWidth()) + xPixelOffset) - w;
        rotPt180.y = ofGetHeight() - ((ypos * (float) ofGetHeight()) + yPixelOffset) - h;
        rotPt270.x =  (ypos * (float) ofGetWidth()) + yPixelOffset;
        rotPt270.y = ofGetHeight() - ((xpos * (float) ofGetHeight()) + xPixelOffset) - w;
        setRotation(currentOrientation);
        updatePosition();
        return this;
    }
    
    
    
};