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


#include "loopControl.h"
#include "EAVIGUI.geomFunctions.h"

namespace EAVIGUI {
    
    
    LoopControl::LoopControl(InterfaceListener *_listener, int _id, int _x, int _y, int w, int h, sharedDataContainer *_data) :
    InterfaceObject(_listener, _id, _x, _y), data(_data) {
        setWidth(w);
        setHeight(h);
        maxCaretDist = w  * 0.3;
        minCaretDist = w * 0.05;
        caretDistRange = maxCaretDist - minCaretDist;
        setIsInteractive(true);
        ofFbo::Settings settings;
        settings.width			= ofNextPow2(w);
        settings.height			= ofNextPow2(h);
        fboWidth = settings.width;
        fboHeight = settings.height;
        settings.useDepth		= false;
        settings.useStencil		= false;
        waveFBO.allocate(settings);
        reset();
    }

    void LoopControl::reset() {
        caretPos.x = cx + maxCaretDist;
        caretPos.y =  cy; 
        start = 0;
        end = 1;
        playHeadPos = 0;
    }

    void LoopControl::drawToBuffer() {
        ofSetColor(0,255,0);
        ofNoFill();
        ofCircle(w/2, h/2, minCaretDist);
        ofCircle(w/2, h/2, maxCaretDist);
        ofSetColor(ofColor::gray);
        ofCircle(caretPos.x, caretPos.y, 80);
//        ofLine(caretPos.x, caretPos.y, cx, cy);
        ofVec2f endPt;
        endPt.x = maxCaretDist;
        endPt.y = 0;
        endPt = endPt.rotateRad(end * TWO_PI);
        endPt += ofVec2f(cx, cy);
//        ofSetColor(100,0,0,255);
//        ofLine(cx, cy, endPt.x, endPt.y);
        ofSetColor(200,100,100,255);
        waveFBO.draw((w - fboWidth) / 2.0, (h - fboHeight) / 2.0);
        float arcEnd = end;
        if (end - start < 0.001) arcEnd = end + 0.001;
        ofSetColor(0,0,200,130);
        ofFill();
        ofPolyline poly;
        poly.addVertex(cx,cy);
        poly.arc(cx, cy, maxCaretDist, maxCaretDist, 360.0 * start, 360.0 * arcEnd, 200);
        poly.close();
        ofBeginShape();
        for( int i = 0; i < poly.getVertices().size(); i++) {
            ofVertex(poly.getVertices().at(i).x, poly.getVertices().at(i).y);
        }
        ofEndShape();
        ofSetColor(100,100,100,200);
        ofLine(cx+minCaretDist,cy,cx+maxCaretDist, cy);
        ofSetColor(255,255,255,255);
        ofVec2f playHeadEndPt(maxCaretDist, 0);
        playHeadEndPt = playHeadEndPt.rotateRad(playHeadPos * TWO_PI);
        ofLine(cx,cy,cx+playHeadEndPt.x, cy+playHeadEndPt.y);
        invalidate();
    }

    void LoopControl::touchDown(ofTouchEventArgs &touch) {
        InterfaceObject::touchDown(touch);
        moveCaret(touch);
    }
    
    void LoopControl::touchMoved(ofTouchEventArgs &touch) {
        InterfaceObject::touchMoved(touch);
        moveCaret(touch);
    }
    
    void LoopControl::touchUp(ofTouchEventArgs &touch) {
        InterfaceObject::touchUp(touch);
        
    }
    
    void LoopControl::moveCaret(ofTouchEventArgs &touch) {
        caretPos.x = touch.x;
        caretPos.y = touch.y;
        float distToC = ofDist(cx,cy,touch.x,touch.y);
        if (distToC < minCaretDist || distToC > maxCaretDist) {
            float touchangle = geom::angleBetween(caretPos.x, caretPos.y, cx, cy);
            caretPos.y = 0;
            caretPos.x = ofClamp(distToC, minCaretDist, maxCaretDist);
            caretPos = caretPos.rotateRad(touchangle);
            caretPos.x += cx;
            caretPos.y += cy;
        }
//        cout << geom::angleBetween(caretPos.x, caretPos.y, cx, cy) << ", " << geom::distBetween(caretPos.x, caretPos.y, cx, cy) << endl;
        float angle = geom::angleBetween(caretPos.x, caretPos.y, cx, cy);
        if (angle < 0) angle += TWO_PI;
        float sampleStart = angle / TWO_PI;
        start = sampleStart;
        float loopSize = (ofDist(caretPos.x, caretPos.y, cx, cy) - minCaretDist) / caretDistRange;
        end = sampleStart + min(max(loopSize, 0.f), 1.0f - sampleStart);
        cout << sampleStart << " : " << end << endl;
        invalidate();
    }

    void LoopControl::updateWaveform(maxiSample *sample) {
        if (sample->length > 0) {
            ofClear(255);
    //        ofSetColor(255,255,255,255);
            waveFBO.begin();
            float wcx = fboWidth / 2.0;
            float wcy = fboHeight / 2.0;
            float waveRadius = ((maxCaretDist + minCaretDist) / 2);
            float numPoints = TWO_PI * waveRadius;
            float ang = TWO_PI/numPoints;
            float sampleInc = (sample->length - 1) / numPoints;
            ofSetColor(ofColor::magenta);
            float wavRange = caretDistRange / 2.0;
            ofVec2f lp(0,0);
            ofNoFill();
            for(int i=0; i < numPoints; i++) {
                float amp = sample->temp[static_cast<int>(floor(i * sampleInc))] / 32767.0;
                ofVec2f p(waveRadius + (amp * wavRange),0);
                p = p.rotateRad(i*ang);
                p.x += wcx;
                p.y += wcy;
                ofSetColor(ofColor::yellow, 200);
                ofCircle(p.x, p.y, 1 + fabs(amp * 7));
                if (i>0) {
                    ofSetColor(ofColor::magenta);
                    ofLine(p,lp);
                }
                lp = p;
            }
            waveFBO.end();
        }
        reset();
    }

    void LoopControl::setPos(float newPos) {
        playHeadPos = newPos;
    }

};
