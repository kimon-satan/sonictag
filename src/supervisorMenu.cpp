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

    infoButton = new EAVIGUI::Label(callback, INFOBUTTON, 0, 0, 100, 60, &EAVIGUI::InterfaceManager::fontList["titles"], "info", ofColor::black);
    infoButton->setRelativePositioning(0.5, 50, 0.5 , 280);
    infoButton->setBackgroundColour(ofColor(255, 255, 255, 245));
    infoButton->setIsInteractive(true);
    infoButton->setHorizontalTextJustification(EAVIGUI::Label::JUSTIFYCENTER);
    infoButton->setRoundedCorners(true);
    menuGroup.push_back(infoButton);

    map = new EAVIGUI::MapControl(callback, MAPCONTROL, 0, 0, 650, 600, grid, &EAVIGUI::InterfaceManager::fontList["small"]);
    map->setRelativePositioning(0.5, -325, 0.5 , -340);
    menuGroup.push_back(map);
    
    EAVIGUI::InterfaceManager::addObjects(menuGroup);
    
//    infoPanel = new EAVIGUI::Panel(callback, INFOPANEL, 0, 0, 700, 700, ofColor(0,0,0,230), ofColor::black);
//    infoPanel->setRelativePositioning(0.5, -infoPanel->getScaledWidth() / 2.0, 0.5 , -infoPanel->getScaledHeight() / 2.0);
//    infoGroup.push_back(infoPanel);

    string infotext = "SONIC TAG\n\n\n"
    "Designed and coded by Mick Grierson and Chris Kiefer,\nwith help from the staff and children at:\n\n"
    "St Francis School, Lincoln\n"
    "Linwood School, Bournemouth\n"
    "Whitefield Schools and Center, Walthamstow, London\n\n"
    "This software was developed as part of the\n'Sound, Image and Brain' project\nat EAVI, Goldsmiths, University of London.\n"
    "It was funded by the Arts & Humanities \nResearch Council, and soundandmusic.org\n\n"
    "http://eavi.goldsmithsdigital.com\n"
    ;
    infoLabel = new EAVIGUI::Label(callback, INFOLABEL, 0, 0, 700, 700, &EAVIGUI::InterfaceManager::fontList["kannada_small"], infotext, ofColor::black);
    infoLabel->setRelativePositioning(0.5, -infoLabel->getScaledWidth() / 2.0, 0.5 , -infoLabel->getScaledHeight() / 2.0);
    infoLabel->setBackgroundColour(ofColor(230, 230, 230, 250));
    infoLabel->setTouchDownColour(ofColor(230, 230, 230, 250));
    infoLabel->setIsInteractive(true);
    infoLabel->setHorizontalTextJustification(EAVIGUI::Label::JUSTIFYCENTER);
    infoLabel->setRoundedCorners(true);
    infoLabel->setVerticalTextJustification(EAVIGUI::Label::JUSTIFYCENTERV);
    infoGroup.push_back(infoLabel);

    EAVIGUI::InterfaceManager::addObjects(infoGroup);

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

void supervisorMenu::showInfo(bool vis) {
    EAVIGUI::InterfaceManager::showHideModalGroup(&infoGroup, vis);
}
