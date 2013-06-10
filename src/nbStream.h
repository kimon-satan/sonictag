//
//  nbStream.h
//  BLERx
//
//  Created by Chris on 26/02/2013.
//
//

#ifndef BLERx_nbStream_h
#define BLERx_nbStream_h

class nbStream {
public:
    nbStream() : minVal(9999), maxVal(-9999), value(0) {updateRange();}
    float newVal(float val);
    float getValue();
private:
    void updateRange();
    float minVal, maxVal, range;
    bool enoughData;
    float value;
};

#endif
