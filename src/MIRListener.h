//
//  MIRListener.h
//  SonicTag3
//
//  Created by Chris on 04/06/2013.
//
//

#ifndef SonicTag3_MIRListener_hpp
#define SonicTag3_MIRListener_hpp


#include "ofxMaxim.h"
#include "ofMain.h"


class MIRListener  {
public:
    MIRListener() {
        env.setAttack(10);
        env.setRelease(10);
        fft.setup(1024, 512, 256);
        mfcc.setup(512, 42, 5, 20, 20000, 44100);
        mfccCoeffs.resize(14, 0);
    }
    
    inline float play(float input){
        env.play(input);
        if (fft.process(input)) {
            mfcc.mfcc(fft.magnitudes, &mfccCoeffs[0]);
            ofSendMessage("fftcomplete");
        }
        return 0;
    };
    
    maxiEnvelopeFollower env;
    maxiFFT fft;
    maxiMFCC mfcc;
    vector<double> mfccCoeffs;
};

#endif
