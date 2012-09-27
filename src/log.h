//
//  log.h
//  sonicTag2
//
//  Created by Chris Kiefer on 11/07/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#ifndef sonicTag2_log_h
#define sonicTag2_log_h

#include <iostream>
#include <fstream>
#include "ofMain.h"
//#include "ofxiPhone.h"
//#include "ofxiPhoneExtras.h"

using namespace std;

class log {
public:
    enum logevents {
        NEWSCENE=0,
        APPSTART,
        APPEND,
        STARTRECORDING,
        STOPRECORDING,
        CLEARBUFFER,
        TOUCHCOORDS, 
        ANGLE,
        ACCEL
    };
    static void init(string folder);
    static void save();
    static void newEntry(logevents e);
    static void write(logevents e);
    static void write(logevents e, string s);
    static void write(logevents e, int i1, int i2);
    static void write(logevents e, float f1);
    static void write(logevents e, float f1, float f2, float f3);
private:
    static fstream f;
};

#endif
