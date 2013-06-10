//
//  nbStream.cpp
//  BLERx
//
//  Created by Chris on 26/02/2013.
//
//

#include "nbStream.h"
#include <cmath>

float nbStream::newVal(float val) {
    if (val < minVal) {
        minVal = val;
        updateRange();
    }
    if (val > maxVal) {
        maxVal = val;
        updateRange();
    }
    value = (val - minVal) / range;
    if (enoughData)
        return value;
    else
        return -1;
}

void nbStream::updateRange() {
    range = fmax(1.0f, maxVal - minVal);
    enoughData = range < 256;    
}

float nbStream::getValue() {
    return value;
}
