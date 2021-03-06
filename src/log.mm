/*
 This file is part of 'Sonic Tag'.
 This software is released under a simplified BSD license, modified for non-commercial use only.
 
 Copyright (c) 2013, M.Grierson, Embodied AudioVisual Interaction Group, Goldsmiths, University of London
 
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are
 met:
 
 * Redistributions of source code must retain the above copyright
 notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above
 copyright notice, this list of conditions and the following disclaimer
 in the documentation and/or other materials provided with the
 distribution.
 * Any redistribution, use, or modification is done solely for
 personal benefit and not for any commercial purpose or for monetary
 gain
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
 For further information:
 http://eavi.goldsmithsdigital.com/sound-image-and-brain/
 http://eavi.goldsmithsdigital.com/sonic-tag/
 
 */


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
