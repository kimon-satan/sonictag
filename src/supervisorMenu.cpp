//
//  supervisorMenu.cpp
//  SonicTag3
//
//  Created by Chris on 20/06/2013.
//
//

#include "supervisorMenu.h"


void supervisorMenu::setup(EAVIGUI::InterfaceListener *callback, vector<vector<baseScene*> > *grid) {
    menuPanel = new EAVIGUI::Panel(callback, MENUPANEL, 0, 0, 700, 700, ofColor(0,0,0,230), ofColor::black);
    menuPanel->setRelativePositioning(0.5, -menuPanel->getScaledWidth() / 2.0, 0.5 , -menuPanel->getScaledHeight() / 2.0);
    menuGroup.push_back(menuPanel);

    lockcb = new EAVIGUI::CheckBox(callback, LOCKCB, 0, 0, 300, 40, &EAVIGUI::InterfaceManager::fontList["subtitles"], "Lock Navigation", ofColor::black);
    lockcb->setRelativePositioning(0.5, -325, 0.5 , 300);
    lockcb->setBackgroundColour(ofColor(255,255,255, 245));
    lockcb->setTouchDownColour(ofColor::gray);
    lockcb->setRoundedCorners(true);
    lockcb->setVerticalTextJustification(EAVIGUI::Label::JUSTIFYCENTERV);
    lockcb->setLeftMargin(10);
    menuGroup.push_back(lockcb);

    doneButton = new EAVIGUI::Label(callback, DONEBUTTON, 0, 0, 100, 60, &EAVIGUI::InterfaceManager::fontList["titles"], "OK", ofColor::black);
    doneButton->setRelativePositioning(0.5, 210, 0.5 , 280);
    doneButton->setBackgroundColour(ofColor(255, 255, 255, 245));
    doneButton->setIsInteractive(true);
    doneButton->setHorizontalTextJustification(EAVIGUI::Label::JUSTIFYCENTER);
    doneButton->setRoundedCorners(true);
    menuGroup.push_back(doneButton);
    
    map = new EAVIGUI::MapControl(callback, MAPCONTROL, 0, 0, 650, 600, grid, &EAVIGUI::InterfaceManager::fontList["small"]);
    map->setRelativePositioning(0.5, -325, 0.5 , -340);
    menuGroup.push_back(map);
    
    EAVIGUI::InterfaceManager::addObjects(menuGroup);

}

void supervisorMenu::setVisible(bool vis) {
//    menuPanel->setVisible(vis);
//    lockcb->setVisible(vis);
//    doneButton->setVisible(true);
    EAVIGUI::InterfaceManager::showHideModalGroup(&menuGroup, vis);
}

void supervisorMenu::setLocation(int nx, int ny) {
    map->setLocation(nx, ny);
}

void supervisorMenu::getLocation(int &lx, int &ly) {
    map->getLocation(lx, ly);
}
