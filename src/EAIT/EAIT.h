//
//  EAIT.h
//  sonicTag2
//
//  Created by Chris Kiefer on 29/06/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#ifndef EAIT_h
#define EAIT_h

//INTERACTION TOOLKIT

#include "Trig.h"
#include "Smoothing.h"

namespace EAIT {

    class autoStream {

    };
    
    /*
     A simple counter
     */
    template <class T>
    class Counter {
    public:
        Counter(T initialValue=0, T mod=1) : value(initialValue), mod(mod) {};
        inline T next() {
            T currVal = value;
            value += mod;
            return currVal;
        };
        inline T getValue() {
            return value;
        }
        inline void setValue(T newVal) {
            value = newVal;
        }
    private:
        T value;
        T mod;
    };

}


#endif
