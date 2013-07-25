/*
 This file is part of 'Sonic Tag'.
 This software is released under a simplified BSD license, modified for non-commercial use only.
 
 Copyright (c) 2013, M.Grierson, Embodied AudioVisual Interaction Group, Goldsmiths, University of London
 
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are
 met:
 
 * Redistributions of source code must retain the above copyright
 notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above
 copyright notice, this list of conditions and the following disclaimer
 in the documentation and/or other materials provided with the
 distribution.
 * Any redistribution, use, or modification is done solely for
 personal benefit and not for any commercial purpose or for monetary
 gain
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
 For further information:
 http://eavi.goldsmithsdigital.com/sound-image-and-brain/
 http://eavi.goldsmithsdigital.com/sonic-tag/
 
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
        BasicTrigger():onThreshold(0.5), offThreshold(0.4), holdTime(2), holdCount(2) {reset();}
        BasicTrigger(T onThreshold, T offThreshold, int holdTime)
        :onThreshold(onThreshold), offThreshold(offThreshold), holdTime(holdTime), holdCount(holdTime) {reset();}
        
        bool newFrame(T sig) {
            trigChanged = false;
            bool isBeat = false;
            holdCount++;
            switch(phase) {
                case WAITING:
                    if (holdCount > holdTime) {
                        if (sig > onThreshold) {
                            isBeat = true;
                            phase = INBEAT;
                            holdCount = 0;
                            trigChanged = true;
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
            holdCount = holdTime;
        }
        
        T onThreshold, offThreshold;
        inline bool justTriggered() {
            return trigChanged;
        }
    protected:
        int holdTime;
        int holdCount;
        bool trigChanged;
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