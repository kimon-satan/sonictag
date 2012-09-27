#include "ofMain.h"
#include "SonicTag3.h"

int main(){
	ofSetupOpenGL(1024,768, OF_FULLSCREEN);			// <-------- setup the GL context

	ofRunApp(new SonicTag3());
}
