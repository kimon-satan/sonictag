//
//  supervisorMenu.h
//  SonicTag3
//
//  Created by Chris on 20/06/2013.
//
//

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
