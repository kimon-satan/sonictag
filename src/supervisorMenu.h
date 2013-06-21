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

class supervisorMenu {
public:
    enum uielements {MENUPANEL=10000, LOCKCB, DONEBUTTON};
    void setup(EAVIGUI::InterfaceListener *callback);
    void setVisible(bool vis);
private:
    EAVIGUI::Panel *menuPanel;
    EAVIGUI::CheckBox *lockcb;
    EAVIGUI::Label *doneButton;
    EAVIGUI::InterfaceObjectGroup menuGroup;
    
};

#endif /* defined(__SonicTag3__supervisorMenu__) */
