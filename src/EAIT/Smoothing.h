//
//  Smoothing.h
//  sonicTag2
//
//  Created by Chris Kiefer on 12/07/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#ifndef sonicTag2_Smoothing_h
#define sonicTag2_Smoothing_h

#include <vector>

namespace EAIT {
    
    template<class T>
    class MovingAverage {
    public:
        MovingAverage() {
            MovingAverage(1,0);            
        }
        MovingAverage(int size, T fillValue=0.0) {
            values.resize(size, fillValue);
            index = 0;
            sampleSize = size;
            cachedValue = 0;
            cacheInvalid = true;            
        }
        
        inline void addSample(T s) {
            values[index] = s;
            index++;
            if(index == sampleSize) index = 0;
            cacheInvalid = true;
        }
        
        inline virtual T value() {
            if (cacheInvalid) {
                T total = 0;
                for(int i = 0; i < sampleSize; i++) {
                    total += values[i];
                }
                cachedValue = total / (T) sampleSize;
                cacheInvalid = false;
            }
            return cachedValue;
        }
        
        void resize(int size) {
            index = 0;
            values.resize(size, 0);
            sampleSize = size;
            cacheInvalid = true;            
        }
        
        void fillWith(T val) {
            for(int i = 0; i < sampleSize; i++) {
                values[i] = val;
            }	
            cacheInvalid = true;            
        }
        
        inline int size() {return values.size();}
    protected:
        std::vector<T> values;
        int index;
        int sampleSize;
        bool cacheInvalid;
        T cachedValue;
    };
    
    typedef MovingAverage<float> MovingAverageF;
    typedef MovingAverage<double> MovingAverageD;
    
    template <class T>
    class MovingRMS : public MovingAverage<T> {
    public:
        MovingRMS():MovingAverage<T>(){};
        MovingRMS(int size, T fillValue=0.0):MovingAverage<T>(size, fillValue){};
        
        T value() {
            if (MovingAverage<T>::cacheInvalid) {
                T total = 0;
                for(int i = 0; i < MovingAverage<T>::sampleSize; i++) {
                    total += (MovingAverage<T>::values[i] * MovingAverage<T>::values[i]);
                }
                MovingAverage<T>::cachedValue = sqrt(total / (T) MovingAverage<T>::sampleSize);
                MovingAverage<T>::cacheInvalid = false;
            }
            return MovingAverage<T>::cachedValue;
            
        }
    };
    
    typedef MovingRMS<float> MovingRMSF;
    typedef MovingRMS<double> MovingRMSD;
    
};

#endif
