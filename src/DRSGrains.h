//
//  DRSGrains.h
//  DRSAppOSX
//
//  Created by Chris Kiefer on 28/08/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#ifndef DRSAppOSX_DRSGrains_h
#define DRSAppOSX_DRSGrains_h

#include "maximilian.h"

#include <list>

typedef unsigned long ulong;

//window functions from http://en.wikipedia.org/wiki/Window_function#High-_and_moderate-resolution_windows

template<typename T>
struct DRShannWinFunctor {
	inline T operator()(ulong windowLength, ulong windowPos) {
		return 0.5 * (1.0 - cos((2.0 * PI * windowPos) / (windowLength - 1)));
	}
};

//this window can produce clicks
template<typename T>
struct DRShammingWinFunctor {
	inline T operator()(ulong windowLength, ulong windowPos) {
		return 0.54 - (0.46 * cos((2.0 * PI * windowPos) / (windowLength - 1)));
	}
};


template<typename T>
struct DRScosineWinFunctor {
	inline T operator()(ulong windowLength, ulong windowPos) {
		return sin((PI * windowPos) / (windowLength - 1));
	}
};

template<typename T>
struct DRSrectWinFunctor {
	inline T operator()(ulong windowLength, ulong windowPos) {
		return 1;
	}
};

template<typename T>
struct DRStriangleWinFunctor {
	inline T operator()(ulong windowLength, ulong windowPos) {
		return (2.0 / (windowLength-1.0)) * (((windowLength-1.0)/2.0) - fabs(windowPos - ((windowLength-1.0)/2.0)));
	}
};


template<typename T>
struct DRStriangleNZWinFunctor {
	//non zero end points
	inline T operator()(ulong windowLength, ulong windowPos) {
		return (2.0 / windowLength) * ((windowLength/2.0) - fabs(windowPos - ((windowLength-1.0)/2.0)));
	}
};


template<typename T, typename F>
class DRSmaxiGrainWindowCache {
public:
	unsigned int cacheSize; 
	
	DRSmaxiGrainWindowCache() {
		cacheSize = maxiSettings::sampleRate / 2.0; //allocate mem for up to 500ms grains
		cache = (T**)malloc(cacheSize * sizeof(T*));
		for(int i=0; i < cacheSize; i++) {
			cache[i] = NULL;
		}
	}
	
	~DRSmaxiGrainWindowCache() {
		for(int i=0; i < cacheSize; i++) {
			if(NULL != cache[i]) {
				free(cache[i]);
			}
		}
        free(cache);
	}
	
	T* getWindow(const unsigned int length) {
		if (NULL == cache[length]) {
			cache[length] = (T*)malloc(length * sizeof(T));
			for(int i=0; i < length; i++) {
				cache[length][i] = F()(length, i);
			}
		}
		return cache[length];
	}
	
private:
	T** cache;
	
};

template<typename T>
class DRSmaxiGrainBase {
public:
	virtual T play() {}
    virtual ~DRSmaxiGrainBase() {}
    bool finished;
};

template<typename T, typename F>
class DRSmaxiGrain : public DRSmaxiGrainBase<T> {
public:
	maxiSample *sample;
    T pos;
	T dur;
	long sampleStartPos;
	long sampleIdx;
	long sampleDur;
	long sampleEndPos;
	T freq;
	T speed;
	T inc;
	T frequency;
	T* window;
    short* buffer;
	/*
	 position between 0.0 and 1.0
	 duration in seconds
	 */
	DRSmaxiGrain(maxiSample *sample, const T position, const T duration, const T speed, DRSmaxiGrainWindowCache<T, F> *windowCache) :sample(sample), pos(position), dur(duration), speed(speed) 
	{
        buffer = sample->temp;
		sampleStartPos = sample->length * pos;
		sampleDur = dur * (T)sample->mySampleRate;
		sampleDurMinusOne = sampleDur - 1;
		sampleIdx = 0;
		this->finished = 0;
		freq = 1.0 / dur;
		sampleEndPos = min(sample->length, sampleStartPos + sampleDur);
		frequency = freq * speed;		
		if (frequency > 0) {
			pos = sampleStartPos;
		}else{
			pos = sampleEndPos;
		}
        if (frequency != 0) {
            inc = sampleDur/(maxiSettings::sampleRate/frequency);
        }else
            inc = 0;
		window = windowCache->getWindow(sampleDur);
		
	}
	
	inline T play() {
		T output = 0.0;
		if (!this->finished) {
			envValue = window[sampleIdx];
			T remainder;
            pos += inc;
            if (pos >= sample->length) 
                pos -= sample->length;
            else if (pos < 0) 
                pos += sample->length;
            
            long posl = floor(pos);
            remainder = pos - posl;
            long a = posl;
            long b = posl+1;
            if (b >= sample->length) {
                b = 0;
            }
            output = (T) ((1-remainder) * buffer[a] +
                               remainder * buffer[b])/32767.0;//linear interpolation
			output *= envValue;
		}
		sampleIdx++;
		if (sampleIdx == sampleDur) this->finished = true;
		return output;
	}
	
private:	   
	DRSmaxiGrain();	
	T envValue;
	ulong sampleDurMinusOne;
};



template <typename T>
class DRSmaxiGrainPlayer {
public:
    typedef list<DRSmaxiGrainBase<T>*> DRSgrainList;
	DRSgrainList grains;
	maxiSample *sample;
	
	DRSmaxiGrainPlayer(maxiSample *sample) : sample(sample) {
	}
	
	void addGrain(DRSmaxiGrainBase<T> *g) {
		grains.push_back(g);
	}
	
	inline T play() {
		T total = 0.0;		
        typename DRSgrainList::iterator it = grains.begin();
		while(it != grains.end()) {
			total += (*it)->play();
			if ((*it)->finished) {
				delete(*it);
				it = grains.erase(it);
			}else{
                it++;
            }
		}
		return total;
	}
};


template<typename T, typename F>
class DRSmaxiPitchStretch {
public:
	T position;
	maxiSample *sample;
	DRSmaxiGrainPlayer<T> *grainPlayer;
	DRSmaxiGrainWindowCache<T,F> windowCache;
	T randomOffset;
    long loopStart, loopEnd, loopLength;
    T looper;
	
	DRSmaxiPitchStretch(maxiSample *sample) : sample(sample) {
		grainPlayer = new DRSmaxiGrainPlayer<T>(sample);
		randomOffset=0.0;
        loopWholeSample();
	}
    
    T getNormalisedPosition() {
        return position / (T) sample->length;
    }
    
    T getPosition() {
        return position;
    }
    
    void setPosition(T pos) {
        position = pos * sample->length;
        position = maxiMap::clamp<T>(position, 0, sample->length-1);
    }
    
    void setLoopStart(T val) {
        loopStart = val * sample->length;
        loopLength = loopEnd - loopStart;
    }
    
    void setLoopEnd(T val) {
        loopEnd = val * sample->length;
        loopLength = loopEnd - loopStart;
    }
	
    void loopWholeSample() {
        loopStart = 0.0;
        loopEnd = sample->length;
        loopLength =sample->length;
		position=0.0;
        looper = 0.0;
    }
    
	~DRSmaxiPitchStretch() {
		delete grainPlayer;
	}
	
	inline T play(T speed, T rate, T grainLength, int overlaps, T posMod=0.0) {
		position = position + rate;
        looper++;
		if (position >= loopEnd) position-= loopLength;
		if (position < loopStart) position += loopLength;
		T cycleLength = grainLength * maxiSettings::sampleRate  / overlaps;
        if (looper > cycleLength + randomOffset) {
            looper -= (cycleLength + randomOffset);
			DRSmaxiGrain<T,F> *g = new DRSmaxiGrain<T, F>(sample, max(min((T)1.0,(position / sample->length) + posMod),(T)0.0), grainLength, speed, &windowCache);			
			grainPlayer->addGrain(g);
            randomOffset = rand() % 10;
		}
		return grainPlayer->play();
	}
	
};

#endif
