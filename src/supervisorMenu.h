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


#ifndef __SonicTag3__supervisorMenu__
#define __SonicTag3__supervisorMenu__

#include <iostream>

#include "EAVIGUI.interfaceManager.h"
#include "baseScene.h"
#include "mapControl.h"

class supervisorMenu {
public:
    enum uielements {MENUPANEL=10000, LOCKCB, DONEBUTTON, MAPCONTROL, INFOBUTTON, INFOPANEL, INFOLABEL};
    void setup(EAVIGUI::InterfaceListener *callback, vector<vector<baseScene*> > *grid);
    void setVisible(bool vis);
    void setLocation(int nx, int ny);
    void getLocation(int &lx, int &ly);
    void showInfo(bool vis);
    
private:
    EAVIGUI::Panel *menuPanel, *infoPanel;
    EAVIGUI::CheckBox *lockcb;
    EAVIGUI::Label *doneButton, *infoButton, *infoLabel;
    EAVIGUI::InterfaceObjectGroup menuGroup, infoGroup;
    EAVIGUI::MapControl *map;
    
};

#endif /* defined(__SonicTag3__supervisorMenu__) */
