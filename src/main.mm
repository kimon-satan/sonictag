#include "ofMain.h"
#include "SonicTag3.h"

int main(){
    ofAppiPhoneWindow * iOSWindow = new ofAppiPhoneWindow();
	
	iOSWindow->enableAntiAliasing(4);
	
//	iOSWindow->enableRetinaSupport();
	
//	ofSetupOpenGL(iOSWindow, 480, 320, OF_FULLSCREEN);
//	ofRunApp(new testApp);
	ofSetupOpenGL(iOSWindow, 1024,768, OF_FULLSCREEN);			// <-------- setup the GL context

	ofRunApp(new SonicTag3());
}
