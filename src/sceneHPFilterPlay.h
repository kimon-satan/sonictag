//
//  sceneHPFilterPlay.h
//  sonicTag2NB
//
//  Created by Chris on 13/03/2013.
//
//

#ifndef __sonicTag2NB__sceneHPFilterPlay__
#define __sonicTag2NB__sceneHPFilterPlay__

#include <iostream>

#include "sceneFilterPlay.h"
using namespace std;

class sceneHPFilterPlay : public sceneFilterPlay {
public:
    void audioRequested( float * output, int bufferSize, int nChannels );
    string getTitle() {return string("HP Filter Play");}
    
};

#endif /* defined(__sonicTag2NB__sceneHPFilterPlay__) */
