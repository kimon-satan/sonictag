//
//  sceneRecord.cpp
//  sonicTag2
//
//  Created by Chris Kiefer on 27/06/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#include <iostream>
#include "sceneRecord.h"
#include "audioFiles.h"
#include "audioCatalogue.h"

void sceneRecord::setup(sharedDataContainer *data) {
    baseScene::setup(data);
    radius = ofGetWidth()/4.0;
    cx = ofGetWidth()/2.0;
    cy = ofGetHeight()/2.0;
    rmsMA.resize(2000);
    recordingArmed = false;
    recordCounter = 0;
    initRecording();
    playing = false;
    nbEnergyTrigger = EAIT::BasicTriggerF(0.3, 0.2, 5);
}

void sceneRecord::update() {
    
}

void sceneRecord::updateBLEVals(vector<float> newVals, float sigAvg) {
    cout << sigAvg << endl;
    bool trig = nbEnergyTrigger.newFrame(sigAvg);
}


void sceneRecord::draw() {
    
    
    float animate = (1 + (3*interpol.lopass(ampValAvg, 0.2)));
    ofEnableSmoothing();
    ofSetCircleResolution(200);
    ofBackground(255,255,255);
    ofFill();
    if (recordingArmed || recording) {
        ofSetColor(200,0,0);
    }else{
        ofSetColor(0,0,0);
    }
    if (recording)
        markerAngle += 0.03;
    ofCircle(cx, cy, radius*animate);
    ofSetColor(255,255,255);
    ofCircle(cx, cy, 0.7 * radius*animate);
    float markerWidth = 0.5;
    float tradius = radius * 1.2 *animate;
    ofTriangle(cx, cy, cx + (cos(markerAngle) * tradius), cy + (sin(markerAngle) * tradius), 
               cx + (cos(markerAngle + markerWidth) * tradius), cy + (sin(markerAngle + markerWidth) * tradius));
}

void sceneRecord::audioRequested( float * output, int bufferSize, int nChannels ) {
    if (playing) {
        for(int i=0; i<bufferSize; i++) {
            output[i] = sharedData->buffer.playOnce();
            if (sharedData->buffer.position >= sharedData->buffer.length) {
                playing = false;
            }
        }
    }
    else {
        memset(output, 0, sizeof(float) * bufferSize * nChannels);
    }
}

void sceneRecord::audioIn( float * input, int bufferSize, int nChannels ) {
    for(int i=0; i < bufferSize; i++) {
        rmsMA.addSample(fabs(input[i]));
    }
    if (recordingArmed)
        if (rmsMA.value() > 0.07) {
            recordingArmed = false;
            initialiseRecording();
            recordCounter = maxiSettings::sampleRate * 2;
        }
    if(recording) {
        ampVal=0;
        for(int i=0; i < bufferSize; i++) {
            sharedData->recordBuffer.push_back(input[i] * 32767.0);
//            sharedData->buffer.loopRecord(input[i], true, 0.0);
            ampVal += fabs(input[i]);
        }
        ampValAvg = ampVal/bufferSize;
        recordCounter -= bufferSize;
        if (recordCounter <= 0 && armedRecord) {
            recording = false;
            finaliseRecording();            
        }
    }
}

void sceneRecord::initialiseRecording() {
    sharedData->recordBuffer.clear();
    recording = true;
    log::write(log::STARTRECORDING);
}


void sceneRecord::touchDown(ofTouchEventArgs &touch){
    if (ofDist(touch.x, touch.y, cx, cy) < radius && touch.id == 0) {
        if (armedRecord) {
        }else{
            initialiseRecording();
        }
    }
}


void sceneRecord::finaliseRecording() {
    recording = false;
    markerAngle = 0;
    if (sharedData->recordBuffer.size() > 44100) {
        stringstream filename;
#ifdef TARGET_OF_IPHONE
        filename << ofxiPhoneGetDocumentsDirectory();
#else
        filename << "/tmp/";
#endif
        filename << "record" << ".wav";
        fstream myFile (filename.str().c_str(), ios::out | ios::binary);
        int mySubChunk1Size = 16;
        int myFormat = 1;
        int myChannels = 1;
        int mySampleRate = maxiSettings::sampleRate;
        int myByteRate = mySampleRate * myChannels * 16 / 8;
        int myBlockAlign = myChannels * 16 / 8;
        int myBitsPerSample = 16;
        int myDataSize = sharedData->recordBuffer.size() * 16 / 8;
        int myChunkSize = 36 + myDataSize;
        // write the wav file per the wav file format
        myFile.seekp (0, ios::beg); 
        myFile.write ("RIFF", 4);
        myFile.write ((char*) &myChunkSize, 4);
        myFile.write ("WAVE", 4);
        myFile.write ("fmt ", 4);
        myFile.write ((char*) &mySubChunk1Size, 4);
        myFile.write ((char*) &myFormat, 2);
        myFile.write ((char*) &myChannels, 2);
        myFile.write ((char*) &mySampleRate, 4);
        myFile.write ((char*) &myByteRate, 4);
        myFile.write ((char*) &myBlockAlign, 2);
        myFile.write ((char*) &myBitsPerSample, 2);
        myFile.write ("data", 4);
        myFile.write ((char*) &myDataSize, 4);
        myFile.write ((char*) &(sharedData->recordBuffer[0]), myDataSize);
        myFile.close();
        
//        cout << "Audio length: " << (sharedData->recordBuffer.size() / (float)maxiSettings::sampleRate) << endl;
        sharedData->buffer.clear();
        sharedData->buffer.load(filename.str());
        sharedData->buffer.autoTrim(0.3, 6000, true, false);
        sharedData->buffer.normalise();
        
        cout << "Audio loaded to buffer\n";
        
        //        audioFiles::writeToM4A(sharedData->recordBuffer, ofxiPhoneGetDocumentsDirectory().append("/test.m4a"));
        sharedData->buffer.save(audioCatalogue::getNextFileName());
        log::write(log::STOPRECORDING);
        playing = true;
    }
    
}

void sceneRecord::touchUp(ofTouchEventArgs &touch){    
    if (0 == touch.id) {
        if (armedRecord) {
            if (!recordingArmed && !recording)
                recordingArmed = true;
        }else{
            if (recording)
                finaliseRecording();
        }
    }
}

void sceneRecord::beginScene() {
    baseScene::beginScene();
    initRecording();
}

void sceneRecord::initRecording() {
    markerAngle = 0.0;
    recording = false;        
}

void sceneRecord::endScene() {
    baseScene::endScene();
    recording = false;
    
}

void sceneRecord::handleInterfaceEvent(int id, int eventTypeId, EAVIGUI::InterfaceObject *object) {
    baseScene::handleInterfaceEvent(id, eventTypeId, object);
}