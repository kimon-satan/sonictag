//
//  audioProcessor.h
//  DRSApp
//
//  Created by Chris Kiefer on 31/07/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#ifndef DRSApp_audioProcessor_h
#define DRSApp_audioProcessor_h

class audioProcessor {
public:
    audioProcessor() {}
    virtual void setSample(maxiSample *samp, int numBars) {sample = samp;}
    bool bypass;
    virtual float play(float input){return 0;};
    int sceneID;
    virtual void resync() {}
protected:
    maxiSample *sample;
};

class passThroughAudioProcessor : public audioProcessor {
public:
    inline float play(float input){return input;};
};


#endif
