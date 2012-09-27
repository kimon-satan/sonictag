//
//  audioCatalogue.cpp
//  sonicTag2
//
//  Created by Chris Kiefer on 09/07/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

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
