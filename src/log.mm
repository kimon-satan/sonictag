//
//  log.cpp
//  sonicTag2
//
//  Created by Chris Kiefer on 11/07/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#include <iostream>
#include "log.h"
#include <sstream>

std::fstream log::f;


void log::init(string folder) {  
    stringstream filename;
    filename << folder << time(NULL) << ".txt";
    f.open(filename.str().c_str(), fstream::out);
}

void log::save() {
    f.close();
}

void log::newEntry(logevents e) {
    f << time(NULL) << "," << (int)e << ",";
}

void log::write(logevents e) {
    log::newEntry(e);
    f << endl;
}

void log::write(logevents e, string s) {
    log::newEntry(e);
    f << "\"" << s << "\"";
    f << endl;
}

void log::write(logevents e, int i1, int i2) {
    log::newEntry(e);
    f << i1 << "," << i2;
    f << endl;
}

void log::write(logevents e, float f1) {
    log::newEntry(e);
    f << f1;
    f << endl;
}

void log::write(logevents e, float f1, float f2, float f3) {
    log::newEntry(e);
    f << f1 << "," << f2 << "," << f3;
    f << endl;
}
