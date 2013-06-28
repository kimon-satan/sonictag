//
//  mapControl.h
//  SonicTag3
//
//  Created by Chris on 27/06/2013.
//
//

#ifndef __SonicTag3__mapControl__
#define __SonicTag3__mapControl__


#include <iostream>

#include "EAVIGUI.interfaceObject.h"
#include <iostream>
#include "sharedData.h"
#include "baseScene.h"

using namespace std;

namespace EAVIGUI {
    
    class MapControl : public InterfaceObject {
    public:
        enum mapControlEvents {MAPCHANGESCENE};
        MapControl(InterfaceListener *_listener, int _id, int _x, int _y, int w, int h, vector<vector<baseScene*> > *_grid, ofTrueTypeFont *_font);
        void setLocation(int nx, int ny);
        void touchUp(ofTouchEventArgs &touch);
        void getLocation(int &lx, int &ly);
    protected:
        void update();
        void drawToBuffer();
        vector<vector<baseScene*> > *grid;
        float xsize, ysize, border;
        ofTrueTypeFont *font;
        int locx, locy, newx, newy;
    };
    
};


#endif /* defined(__SonicTag3__mapControl__) */
