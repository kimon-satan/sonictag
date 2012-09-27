//
//  sceneFilter.h
//  DRSApp
//
//  Created by Chris Kiefer on 01/08/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#ifndef DRSApp_sceneFilter_h
#define DRSApp_sceneFilter_h

#include "sceneGain.h"
#include "circularDial.h"

template<typename T>
class DRSmaxiFilter { 	
	T gain;
	T input;
	T output;
	T inputs[10];
	T outputs[10];
	T cutoff1;
	T x;//speed
	T y;//pos
	T z;//pole
	T c;//filter coefficient
    T r;
    T lastCutoff, lastRes;
    
public:
	DRSmaxiFilter():x(0.0), y(0.0), z(0.0), c(0.0), lastCutoff(-1), lastRes(-1){};
	T cutoff;
	T resonance;
	inline T lores(const T input,T cutoff1, T resonance) {
        if (cutoff != lastCutoff || resonance != lastRes) {
            lastCutoff = cutoff;
            lastRes = resonance;
            cutoff=cutoff1*0.5;
            if (cutoff<10) cutoff=10;
            if (cutoff>(maxiSettings::sampleRate*0.5)) cutoff=(maxiSettings::sampleRate*0.5);
            z=cos(TWOPI*cutoff/maxiSettings::sampleRate);
            c=2-2*z;
            if (resonance<1.) resonance = 1.;
            r=(sqrt(2.0)*sqrt(-pow((z-1.0),3.0))+resonance*(z-1))/(resonance*(z-1));
        }
        x=x+(input-y)*c;
        y=y+x;
        x=x*r;
        output=y;
        return(output);        
    }
//	double hires(double input,double cutoff1, double resonance);
//	double bandpass(double input,double cutoff1, double resonance);
//	double lopass(double input,double cutoff);
//	double hipass(double input,double cutoff);
	
};


class audioProcessorFilter : public audioProcessor {
public:
    audioProcessorFilter() {freq = 15000; res = 1;}
    float play(float input) {return filt.lores(input, freq, res);}
    DRSmaxiFilter<float> filt;
    float freq;
    float res;
};


class sceneFilter : public sceneGain {
public:
    string getTitle() {return string("Low Filter");}
    audioProcessor* getAudioProcessor() {return new audioProcessorFilter();};  
    void setAudioProcessor(audioProcessor* currProcessor);
    
    void handleInterfaceEvent(int id, int eventTypeId, EAVIGUI::InterfaceObject *object);
    string getSubTitle() {return "Drag the circular bar to cut out high frequencies.";};

protected:
    
};


#endif
