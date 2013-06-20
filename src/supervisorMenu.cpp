//
//  supervisorMenu.cpp
//  SonicTag3
//
//  Created by Chris on 20/06/2013.
//
//

#include "supervisorMenu.h"


void supervisorMenu::setup(EAVIGUI::InterfaceListener *callback) {
    lockcb = new EAVIGUI::CheckBox(callback, LOCKCB, 0, 0, 400, 40, &EAVIGUI::InterfaceManager::fontList["subtitles"], "Lock Navigation", ofColor::red);
    lockcb->setRelativePositioning(0.5, -lockcb->getScaledWidth() / 2.0, 0.5 , -lockcb->getScaledHeight() / 2.0);
    lockcb->setBackgroundColour(ofColor(0,0,0,255));
    EAVIGUI::InterfaceManager::addObject(lockcb);

    menuPanel = new EAVIGUI::Panel(callback, MENUPANEL, 0, 0, 500, 700, ofColor(0,255,0,100), ofColor::black);
    menuPanel->setRelativePositioning(0.5, -menuPanel->getScaledWidth() / 2.0, 0.5 , -menuPanel->getScaledHeight() / 2.0);
    EAVIGUI::InterfaceManager::addObject(menuPanel);
}

void supervisorMenu::setVisible(bool vis) {
    menuPanel->setVisible(vis);
    lockcb->setVisible(vis);
}
