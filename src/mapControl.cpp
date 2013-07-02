//
//  mapControl.cpp
//  SonicTag3
//
//  Created by Chris on 27/06/2013.
//
//

#include "mapControl.h"


namespace EAVIGUI {
    
    MapControl::MapControl(InterfaceListener *_listener, int _id, int _x, int _y, int w, int h, vector<vector<baseScene*> > *_grid, ofTrueTypeFont *_font)
    : InterfaceObject(_listener, _id, _x, _y, w, h), grid(_grid), font(_font) {
        setWidth(w);
        setHeight(h);
        setIsInteractive(true);
        border = 10;
        float wb = w - (2.0 * border);
        float hb = h - (2.0 * border);
        xsize = wb / (float) grid->size();
        ysize = hb / (float) grid->at(0).size();
        locx=locy=0;
    }

    void MapControl::update() {
        
    }
    
    void MapControl::drawToBuffer() {
        ofFill();
        ofSetColor(50,50,50, 100);
        roundedRect(1,1,w,h, 30);
        for(int i=0; i < grid->size(); i++) {
            for(int j=0; j < grid->at(0).size(); j++) {
                bool isCurrPos = i == locx && j == locy;
                ofSetLineWidth(isCurrPos ? 4 : 1);
                ofSetColor(grid->at(i).at(j) == NULL ? ofColor::gray : isCurrPos ? ofColor(200,200,200,255) : ofColor::white, 230);
                ofNoFill();
                float left = border + (i*xsize);
                float top = border + (j*ysize);
                roundedRect(left + 3, top + 3, xsize - 6, ysize - 6, 10);
                ofSetColor(255,255,255,255);
                if (grid->at(i).at(j) != NULL) {
                    float stringW = font->stringWidth(grid->at(i).at(j)->getTitle());
//                    font->drawString(grid->at(i).at(j)->getTitle(), left + 3 + ((xsize - stringW) / 2.0), top + (ysize / 2.0));
                    ofDrawBitmapString(grid->at(i).at(j)->getTitle(), left + 5, top + (ysize / 2.0));
                }
                
            }
        }
    }
    
    void MapControl::setLocation(int nx, int ny) {
        locx = nx;
        locy = ny;
        invalidate();
    }
    
    void MapControl::touchUp(ofTouchEventArgs &touch) {
        newx = floor(touch.x / xsize);
        newy = floor(touch.y / ysize);

        sendCallback(MAPCHANGESCENE);
    }

    void MapControl::getLocation(int &lx, int &ly) {
        lx = newx;
        ly = newy;
    }

};

