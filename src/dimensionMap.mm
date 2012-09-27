//
//  dimensionMap.cpp
//  DRSAppOSX
//
//  Created by Chris Kiefer on 24/08/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#include <iostream>

#include "dimensionMap.h"
#include "dimensions.h"

void dimensionMap::setup(sharedDataContainer *data) {
    sharedData = data;


    mapImage = new EAVIGUI::FullScreenImage(this, MAP, 0, 0, "map/map_background.png");
    mapMask.loadImage("map/Dimension_Map-Mask.png");
    interface.push_back(mapImage);
    EAVIGUI::InterfaceManager::addObjects(interface);
    EAVIGUI::InterfaceManager::setGroupVisibility(interface, true);

    goButton = new EAVIGUI::Label(this, GO, 0, 0, 600, 600,
                                  &EAVIGUI::InterfaceManager::fontList["big"],
                                  "",
                                  ofColor(220,0,0));
    goButton->setText("GO!");
    goButton->pulsate = true;
    goButton->fitToText();
    goButton->fadeTime = 0;
    goButton->setIsInteractive(true);
//    goButton->setAnchorPoint(0.5, 0.5);
    goButton->setRelativePositioning(0.98, -goButton->getScaledWidth(), 0.98, -goButton->getScaledHeight());
    EAVIGUI::InterfaceManager::addObject(goButton);

#ifndef TARGET_OF_IPHONE
    appStoreLabel = new EAVIGUI::Label(this, GO, 0, 0, 600, 600,
                                  &EAVIGUI::InterfaceManager::fontList["subtitles"],
                                  "",
                                  ofColor(255, 255, 255));
    appStoreLabel->setText("Play this at home - search the App Store for 'Dean Rodney Singers'");
    appStoreLabel->fitToText();
    appStoreLabel->fadeTime = 0;
    appStoreLabel->setIsInteractive(false);
    //    goButton->setAnchorPoint(0.5, 0.5);
    appStoreLabel->setRelativePositioning(0.5, -appStoreLabel->getScaledWidth() / 2.0, 0.02, 0);
    EAVIGUI::InterfaceManager::addObject(appStoreLabel);
    appStoreLabel->setVisible(true);
#endif
    
    chinaTitle = new EAVIGUI::ImageButton(this, CHINATITLE, 0, 0, "map/map_china_title.png");
    chinaTitle->setRelativePositioning(0.5, -chinaTitle->getScaledWidth() / 2.0, 0.9, -chinaTitle->getScaledHeight());
    EAVIGUI::InterfaceManager::addObject(chinaTitle);

    ukTitle = new EAVIGUI::ImageButton(this, UKTITLE, 0, 0, "map/map_uk_title.png");
    ukTitle->setRelativePositioning(0.5, -ukTitle->getScaledWidth() / 2.0, 0.9, -ukTitle->getScaledHeight());
    EAVIGUI::InterfaceManager::addObject(ukTitle);

    germanyTitle = new EAVIGUI::ImageButton(this, GERMANYTITLE, 0, 0, "map/map_germany_title.png");
    germanyTitle->setRelativePositioning(0.5, -germanyTitle->getScaledWidth() / 2.0, 0.9, -germanyTitle->getScaledHeight());
    EAVIGUI::InterfaceManager::addObject(germanyTitle);

    brazilTitle = new EAVIGUI::ImageButton(this, BRAZILTITLE, 0, 0, "map/map_brazil_title.png");
    brazilTitle->setRelativePositioning(0.5, -brazilTitle->getScaledWidth() / 2.0, 0.9, -brazilTitle->getScaledHeight());
    EAVIGUI::InterfaceManager::addObject(brazilTitle);
    
    croatiaTitle = new EAVIGUI::ImageButton(this, CROATIATITLE, 0, 0, "map/map_croatia_title.png");
    croatiaTitle->setRelativePositioning(0.5, -croatiaTitle->getScaledWidth() / 2.0, 0.9, -croatiaTitle->getScaledHeight());
    EAVIGUI::InterfaceManager::addObject(croatiaTitle);
    
    southAfricaTitle = new EAVIGUI::ImageButton(this, SATITLE, 0, 0, "map/map_southafrica_title.png");
    southAfricaTitle->setRelativePositioning(0.5, -southAfricaTitle->getScaledWidth() / 2.0, 0.9, -southAfricaTitle->getScaledHeight());
    EAVIGUI::InterfaceManager::addObject(southAfricaTitle);
    
    japanTitle = new EAVIGUI::ImageButton(this, JAPANTITLE, 0, 0, "map/map_japan_title.png");
    japanTitle->setRelativePositioning(0.5, -japanTitle->getScaledWidth() / 2.0, 0.9, -japanTitle->getScaledHeight());
    EAVIGUI::InterfaceManager::addObject(japanTitle);
    
    loading = new EAVIGUI::LabelAnimation(this, LOADING, 0, 0, 500, 200, 
                                          &EAVIGUI::InterfaceManager::fontList["bigger"],
                                          "",
                                          ofColor(0,255,0));
    loading->setText("LOADING");
    loading->setRelativePositioning(0.5, -loading->getScaledWidth()/2.0, 0.5, -loading->getScaledHeight()/2.0);
    EAVIGUI::InterfaceManager::addObject(loading);
    
    currTitle = chinaTitle;
}

DRSDATA::dimensions ColToDimension(int r) {
    DRSDATA::dimensions dim = DRSDATA::BRAZIL;
    switch (r) {
        case 0:
            dim = DRSDATA::BRAZIL;
            break;
        case 181:
            dim = DRSDATA::UK;
            break;
        case 61:
            dim = DRSDATA::CROATIA;
            break;
        case 33:
            dim = DRSDATA::GERMANY;
            break;
        case 89:
            dim = DRSDATA::SOUTH_AFRICA;
            break;
        case 121:
            dim = DRSDATA::CHINA;
            break;
        case 148:
            dim = DRSDATA::JAPAN;
            break;
    }
    return dim;
}

void dimensionMap::handleInterfaceEvent(int id, int eventTypeId, EAVIGUI::InterfaceObject *object) {
    cout << "Map: " << id << ", " << eventTypeId << endl;
    switch(id) {
        case MAP: 
            if (eventTypeId == EAVIGUI::InterfaceObject::TOUCHUP) {
                cout << mapImage->touchPoint.x << ", " << mapImage->touchPoint.y << endl;
                ofColor touchCol = mapMask.getColor(mapImage->touchPoint.x, 
                                                    mapImage->touchPoint.y);
                cout << (int) touchCol.r << endl;
                currTitle->setVisible(false);
                if (255 == touchCol.r) {
                    goButton->setVisible(false);
                }else{
                    goButton->setVisible(true);
                    sharedData->currentDimension = ColToDimension(touchCol.r);
                    switch(sharedData->currentDimension) {
                        case DRSDATA::CHINA:
                            chinaTitle->setVisible(true);
                            currTitle = chinaTitle;
                            break;
                        case DRSDATA::UK:
                            ukTitle->setVisible(true);
                            currTitle = ukTitle;
                            break;
                        case DRSDATA::CROATIA:
                            croatiaTitle->setVisible(true);
                            currTitle = croatiaTitle;
                            break;
                        case DRSDATA::GERMANY:
                            germanyTitle->setVisible(true);
                            currTitle = germanyTitle;
                            break;
                        case DRSDATA::JAPAN:
                            japanTitle->setVisible(true);
                            currTitle = japanTitle;
                            break;
                        case DRSDATA::SOUTH_AFRICA:
                            southAfricaTitle->setVisible(true);
                            currTitle = southAfricaTitle;
                            break;
                        case DRSDATA::BRAZIL:
                            brazilTitle->setVisible(true);
                            currTitle = brazilTitle;
                            break;
                    }
                    sharedData->currSong = &assets::dimensions[sharedData->currentDimension].songs[0];                    
                }
            }
            break;
        case GO:
            if (eventTypeId == EAVIGUI::InterfaceObject::TOUCHUP) {
                cout << "Go!\n";
                //hide everything
//                showHide(false);
                goButton->setVisible(false);
                loading->setVisible(true);
                //load
                ofSendMessage("load");
            }
            break;
        
    }
}



void dimensionMap::showHide(bool vis) {
    goButton->setVisible(vis);
    chinaTitle->setVisible(vis);
    brazilTitle->setVisible(vis);
    ukTitle->setVisible(vis);
    germanyTitle->setVisible(vis);
    southAfricaTitle->setVisible(vis);
    japanTitle->setVisible(vis);
    croatiaTitle->setVisible(vis);
    mapImage->setVisible(vis);    
    loading->setVisible(vis);
#ifndef TARGET_OF_IPHONE
    appStoreLabel->setVisible(vis);
#endif
}

void dimensionMap::show() {
    mapImage->setVisible(true);    
#ifndef TARGET_OF_IPHONE
   appStoreLabel->setVisible(true);
#endif
    
}