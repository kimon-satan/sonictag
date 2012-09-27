//
//  dimensionMap.h
//  DRSAppOSX
//
//  Created by Chris Kiefer on 24/08/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#ifndef DRSAppOSX_dimensionMap_h
#define DRSAppOSX_dimensionMap_h

#include "interfaceManager.h"
#include "EAIT.h"
#include "ofMain.h"
#include "sharedData.h"
#include "labelAnimation.h"

class dimensionMap : public EAVIGUI::InterfaceListener  {
public:
        
    void setup(sharedDataContainer *data);
    void update();
    void handleInterfaceEvent(int id, int eventTypeId, EAVIGUI::InterfaceObject *object);
    void showHide(bool vis);
    void show();
    
    EAVIGUI::InterfaceObjectGroup interface;
    EAVIGUI::FullScreenImage *mapImage;    
    EAVIGUI::ImageButton *chinaTitle, *ukTitle, *germanyTitle, *japanTitle, *croatiaTitle, *southAfricaTitle, *brazilTitle, *currTitle;
    EAIT::Counter<int> objectIDCounter;
    ofImage mapMask;
    EAVIGUI::Label *goButton, *appStoreLabel;
    EAVIGUI::LabelAnimation *loading;
    
    enum IDs {
        MAP, CHINATITLE, UKTITLE, GERMANYTITLE, JAPANTITLE, CROATIATITLE, SATITLE, BRAZILTITLE, GO, LOADING
    };
    sharedDataContainer *sharedData;
};

#endif
