//
//  audioFiles.cpp
//  sonicTag2
//
//  Created by Chris Kiefer on 09/07/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#include <iostream>
#include "audioFiles.h"
#include <AudioToolbox/AudioToolbox.h>

//void audioFiles::writeToM4A(vector<short> data, string filename) {
//    NSString *file = [NSString stringWithUTF8String:filename.c_str()];
//    CFURLRef url1 = CFURLCreateWithFileSystemPath ( NULL, (CFStringRef)file, kCFURLPOSIXPathStyle, false );
//    AudioStreamBasicDescription stream;
//    stream.mSampleRate = 44100;
////    stream.mFormatID = 
////    OSStatus ret = AudioFileCreateWithURL(url1, kAudioFileM4AType,); 
//}