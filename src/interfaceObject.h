
#ifndef _INTERFACE_OBJECT_H
#define _INTERFACE_OBJECT_H

#include "ofMain.h"
#include "TargetConditionals.h"


#ifdef TARGET_OF_IPHONE
    #include "ofxiPhoneAlerts.h"
#endif

namespace EAVIGUI {

    class InterfaceObject;


    class InterfaceListener {
    public:
        virtual void handleInterfaceEvent(int id, int eventTypeId, InterfaceObject *object) {};
    };

    enum mouseStates {
        SOMEWHERELSE, OVER, PRESSED
    };

    enum rotations {
        ROT0, ROT90, ROT180, ROT270
    };

    enum rotationModes {
        ROTMODE_NONE, ROTMODE_REFLECT, ROTMODE_ROTATE, ROTMODE_SPECIFY
    };

    class InterfaceObject 
#ifdef TARGET_OF_IPHONE
    : public ofxiPhoneAlertsListener 
#endif
    {

    public:

        enum InterfaceManagerEvents {
            TOUCHDOUBLETAP, TOUCHDOWN, TOUCHMOVED, TOUCHUP, MOUSEPRESSED, MOUSERELEASED, MOUSEDRAGGED, MOUSEMOVED
        };
        
        
        InterfaceObject(InterfaceListener *_listener, int _id, int _x, int _y);
        InterfaceObject(InterfaceListener *_listener, int _id, int _x, int _y, int _w, int _h);
        ~InterfaceObject();

        virtual void setup();
        virtual void update();
        void draw();
        virtual void mouseMoved( int x, int y );
        virtual void mouseExit();
        virtual void mousePressed( int x, int y, int button=0 );
        virtual void mouseReleased();
        virtual void mouseReleased(int x, int y, int button );
        virtual void mouseDragged(int x, int y, int button);
        virtual void setEnabled(bool newEnabled);
        virtual void touchDown(ofTouchEventArgs &touch);
        virtual void touchUp(ofTouchEventArgs &touch);
        virtual void touchDoubleTap(ofTouchEventArgs &touch);
        virtual void touchMoved(ofTouchEventArgs &touch);
        virtual void touchExit();
        
        
        void addChild(InterfaceObject* child);
        bool hasChildren();
        void invalidate();
        void setVisible(bool val, bool noFade = false);
        bool isVisible();
        bool isInteractive();
        void setIsInteractive(bool val) {interactive = val;}
        InterfaceObject* getParent();
        void setParent(InterfaceObject* newParent);
        void setRotation(rotations rot);
        int getWidth();
        int getHeight();
        int getScaledWidth();
        int getScaledHeight();
        void setWidth(int width);
        void setHeight(int height);
        ofRectangle getRectWithRotation();
        
        virtual void deviceOrientationChanged(int newOrientation);
        void updatePosition();
        InterfaceObject* setNoRotation(){rotMode = ROTMODE_NONE; return this;}
        InterfaceObject* setRotationPoints(ofPoint r90, ofPoint r180, ofPoint r270);
        InterfaceObject* setRotationAroundCenter();
        InterfaceObject* setRelativePositioning(float xpos, float ypos);
        InterfaceObject* setRelativePositioning(float xpos, int xPixelOffset, float ypos, int yPixelOffset);
        void transformTouchForRotation(ofTouchEventArgs &touch);
        
        virtual bool canInteractAt(int x, int y); //accept touch/mouse event here? or pass on to next object

        
        rotationModes rotMode;
        ofPoint rotPt0, rotPt90, rotPt180, rotPt270;
//        ofRectangle rect0, rect90, rect180, rect270;
        vector<InterfaceObject*>* getChildren();
        int x, y;
        InterfaceListener *listener;
        int id;
        int red,green,blue,alpha;
        ofTouchEventArgs *touchArgs;
        int rotation;
        int xRotShift, yRotShift;
        int fadeTime;
        int fadeInTimeStamp, fadeOutTimeStamp;
        
        void setScale(float newScale);
        void setAnchorPoint(float ax, float ay);
        void getAnchorPoint(float &ax, float &ay);

        bool pulsate;
        float pulsateSpeed;
        float pulsateMin, pulsateMax;
        
    protected:
        InterfaceObject();
        void init(InterfaceListener *_listener, int _id, int _x, int _y);
        virtual void drawToBuffer();
        virtual void postDrawToBuffer();  //use this to do something with fbo?
        void sendCallback(int eventTypeId);
        void sendTouchCallback(int eventTypeId, ofTouchEventArgs &touch);
        void calcRotShifts();
        void calcScaleMods();
//        void updateRects();
        ofFbo *tex;
        bool invalidated;
        
        vector<InterfaceObject*> children;
        bool visible;
        mouseStates mouseState;
        InterfaceObject* parent;
        bool interactive;
        int w, h;
        
        float scale, totalScale, xScaleMod, yScaleMod;
        int fboWidth, fboHeight;
        float anchorX, anchorY;
        bool deviceScalingOn;
        void setDeviceScaling(bool val);
        rotations currentOrientation;
    private:
        void show();
        void hide();
        void allocateFBO();
        void deallocateFBO();
        bool allocated;



        
    };

};


#endif

