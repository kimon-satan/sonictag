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
#include "audioCatalogue.h"
#include <sstream>
/*
 keeps db of filenames so user can move back and forth between old recordings
 file name format: "recXXX.wav" where xxx if number of recording
 */

int audioCatalogue::lowestFile = 0;
int audioCatalogue::numberOfRecordings = 0;
int audioCatalogue::highestFile = -1;
int audioCatalogue::currentFile = -1;
string audioCatalogue::folder = "";

int maxRecordings = 40;

string getDataFolder() {
#ifdef TARGET_OF_IPHONE    
    return ofxiPhoneGetDocumentsDirectory();
#else
    return ofToDataPath("");
#endif
}

void audioCatalogue::scan() {
    folder = getDataFolder();
    lowestFile = INT_MAX;
    NSError *error;
    NSArray *dirContents = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:[NSString stringWithUTF8String:folder.c_str()] error:&error];
    NSString *match = @"cat*.wav";
    NSPredicate *predicate = [NSPredicate predicateWithFormat:@"SELF like %@", match];
    NSArray *results = [dirContents filteredArrayUsingPredicate:predicate];
    for(int i=0; i < results.count; i++) {
        NSString *catIdxText = [[results objectAtIndex:i] substringWithRange:NSMakeRange(3, [[results objectAtIndex:i] length] - 7)];
        int catIdx = [catIdxText intValue];
        if (catIdx < lowestFile)
            lowestFile = catIdx;
        if (catIdx > highestFile)
            highestFile = catIdx;
    }
    numberOfRecordings = results.count;
    currentFile = highestFile;
    cout << "Catalogue: lowest: " << lowestFile << ", highest: " << highestFile << endl;
}

void audioCatalogue::deleteOldRecordings() {
    folder = getDataFolder();
    NSError *error;
    NSString *path = [NSString stringWithUTF8String:folder.c_str()];
    NSArray *dirContents = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:path error:&error];
    NSString *match = @"cat*.wav";
    NSPredicate *predicate = [NSPredicate predicateWithFormat:@"SELF like %@", match];
    NSArray *results = [dirContents filteredArrayUsingPredicate:predicate];
    for(int i=0; i < results.count; i++) {
        NSString *catIdxText = [[results objectAtIndex:i] substringWithRange:NSMakeRange(3, [[results objectAtIndex:i] length] - 7)];
        int catIdx = [catIdxText intValue];
        cout << [[results objectAtIndex:i] UTF8String] << endl;
        if (catIdx < highestFile - maxRecordings) {
            cout << "delete\n";
            NSString *fullFilename = [NSString stringWithFormat:@"%@%@",path,[results objectAtIndex:i]];
//            NSLog(fullFilename);
            [[NSFileManager defaultManager] removeItemAtPath:fullFilename error:&error];
        }
    }
}


string audioCatalogue::makeFilename(int idx) {
    stringstream f;
    f << folder << "cat" << idx << ".wav";
    return f.str();
}
string audioCatalogue::getNextFileName() {
    highestFile++;
    currentFile++;
    return makeFilename(highestFile);
}

string audioCatalogue::prevRecording() {
    if (currentFile > 0) {
        currentFile--;
    }
    return makeFilename(currentFile);
}

string audioCatalogue::nextRecording() {
    if (currentFile < highestFile) {
        currentFile++;
    }
    return makeFilename(currentFile);
}
