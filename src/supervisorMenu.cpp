//
//  supervisorMenu.cpp
//  SonicTag3
//
//  Created by Chris on 20/06/2013.
//
//

#include "supervisorMenu.h"


void supervisorMenu::setup(EAVIGUI::InterfaceListener *callback) {
    menuPanel = new EAVIGUI::Panel(callback, MENUPANEL, 0, 0, 500, 700, ofColor(0,255,0,230), ofColor::black);
    menuPanel->setRelativePositioning(0.5, -menuPanel->getScaledWidth() / 2.0, 0.5 , -menuPanel->getScaledHeight() / 2.0);
    menuGroup.push_back(menuPanel);

    lockcb = new EAVIGUI::CheckBox(callback, LOCKCB, 0, 0, 300, 40, &EAVIGUI::InterfaceManager::fontList["subtitles"], "Lock Navigation", ofColor::white);
    lockcb->setRelativePositioning(0.5, -230, 0.5 , 300);
    lockcb->setBackgroundColour(ofColor(0, 0, 255, 245));
    menuGroup.push_back(lockcb);

    doneButton = new EAVIGUI::Label(callback, DONEBUTTON, 0, 0, 100, 60, &EAVIGUI::InterfaceManager::fontList["titles"], "OK", ofColor::black);
    doneButton->setRelativePositioning(0.5, 130, 0.5 , 280);
    doneButton->setBackgroundColour(ofColor(255, 255, 255, 245));
    doneButton->setIsInteractive(true);
    menuGroup.push_back(doneButton);
    
    EAVIGUI::InterfaceManager::addObjects(menuGroup);

}

void supervisorMenu::setVisible(bool vis) {
//    menuPanel->setVisible(vis);
//    lockcb->setVisible(vis);
//    doneButton->setVisible(true);
    EAVIGUI::InterfaceManager::showHideModalGroup(&menuGroup, vis);
}
