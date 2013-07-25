/*
 This file is part of 'Sonic Tag'.
 This software is released under a simplified BSD license, modified for non-commercial use only.
 
 Copyright (c) 2013, M.Grierson, Embodied AudioVisual Interaction Group, Goldsmiths, University of London
 
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are
 met:
 
 * Redistributions of source code must retain the above copyright
 notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above
 copyright notice, this list of conditions and the following disclaimer
 in the documentation and/or other materials provided with the
 distribution.
 * Any redistribution, use, or modification is done solely for
 personal benefit and not for any commercial purpose or for monetary
 gain
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
 For further information:
 http://eavi.goldsmithsdigital.com/sound-image-and-brain/
 http://eavi.goldsmithsdigital.com/sonic-tag/
 
 */

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
                float left = border + (i*xsize);
                float top = border + (j*ysize);
                if (isCurrPos) {
                    ofFill();
                    ofSetColor(255,255,255,200);
                    roundedRect(left + 3, top + 3, xsize - 6, ysize - 6, 20);
                }
                ofNoFill();
                ofSetColor(grid->at(i).at(j) == NULL ? ofColor::gray : isCurrPos ? ofColor(200,200,200,255) : ofColor::white, 230);
                roundedRect(left + 3, top + 3, xsize - 6, ysize - 6, 20);
                ofSetColor(isCurrPos ? ofColor::black : ofColor::white);
                if (grid->at(i).at(j) != NULL) {
                    ofDrawBitmapString(grid->at(i).at(j)->getTitle(), left + 10, top + (ysize / 2.0));
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

