//
//  audioCatalogue.h
//  sonicTag2
//
//  Created by Chris Kiefer on 09/07/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#ifndef sonicTag2_audioCatalogue_h
#define sonicTag2_audioCatalogue_h

#include "ofMain.h"

#ifdef TARGET_OF_IPHONE
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#endif

#include <vector>

class audioCatalogue {
public:
    static void scan();
    static string getNextFileName();
    static string prevRecording();
    static string nextRecording();
    static string makeFilename(int idx);    
    static string folder;
    static void deleteOldRecordings();
    static int lowestFile, highestFile, currentFile;
    static int numberOfRecordings;
};




#endif
