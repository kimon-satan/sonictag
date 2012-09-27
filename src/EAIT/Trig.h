/*
 *
 *  Created by Chris on 26/10/2011.
 *  Copyright 2011 Goldsmiths Creative Computing. All rights reserved.
 *
 */

#pragma once
#include <limits>


namespace EAIT {
    
    template <class T>
    class BasicTrigger {
    public:
        enum beatPhases {
            WAITING, INBEAT
        };
        beatPhases phase;
        BasicTrigger():onThreshold(0.5), offThreshold(0.4), holdTime(2) {reset();}
        BasicTrigger(T onThreshold, T offThreshold, int holdTime)
        :onThreshold(onThreshold), offThreshold(offThreshold), holdTime(holdTime) {reset();}

        bool newFrame(T sig) {
            bool isBeat = false;
            holdCount++;
            switch(phase) {
                case WAITING:
                    if (holdCount > holdTime) {
                        if (sig > onThreshold) {
                            isBeat = true;
                            phase = INBEAT;
                            holdCount = 0;
                        }
                    }
                    break;
                case INBEAT:
                    if (sig < offThreshold) {
                        phase = WAITING;
                    }
                    break;
            }
            return phase == INBEAT;
            
        }

        void reset() {
            phase = WAITING;
            holdCount = std::numeric_limits<int>::max()-1;
        }
        
        T onThreshold, offThreshold;
    protected:
        int holdTime;
        int holdCount;
    };

    typedef BasicTrigger<float> BasicTriggerF;
    typedef BasicTrigger<double> BasicTriggerD;
    
    template <class T>
    class ChangeTrigger {
    public:
        T value;
        unsigned int holdTime, holdCount;
        T threshold;
        
        ChangeTrigger(T initValue=0, unsigned int holdTime=0, T threshold = 0) :
                        value(initValue), holdTime(holdTime), threshold(threshold) {
            
        }
        
        bool newFrame(T newValue) {
            bool trig = fabs(newValue - value) != 0;
            value = newValue;
            if (trig) {
                holdCount = 0;
                holding = true;
            }
            if (holding) {
                if (holdCount == holdTime) {
                    holding = false;
                }else{
                    trig = false;
                    holdCount++;
                }
            }
            return trig;
        }

    private:
        bool holding;
    };
    
    typedef ChangeTrigger<int> ChangeTriggerI;
    typedef ChangeTrigger<float> ChangeTriggerF;
    typedef ChangeTrigger<double> ChangeTriggerD;
    
    class Flag {
    public:
        Flag() {
            value = false;
        }
        void set() {
            value = true;
        }
        bool test() {
            bool ret = value;
            if (value) value = false;
            return ret;
        }
    protected:
        bool value;
    };
}