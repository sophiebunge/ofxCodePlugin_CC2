#include "ofApp.h"
#include "ofMain.h"

//========================================================================
int main() {

	//Use ofGLFWWindowSettings for more options like multi-monitor fullscreen
	ofGLWindowSettings settings;
	settings.setSize(1024, 768);
	settings.windowMode = OF_WINDOW;

	// FOR WHEN WE WANT TO HIDE THE APP IN THE BACKGROUND, comment out above
	// ofGLFWWindowSettings settings;
	// settings.visible = false; // hides the window
	// settings.width = 1024;
	// settings.height = 768;
	// ofCreateWindow(settings);

	// ofRunApp(new ofApp());

	auto window = ofCreateWindow(settings);

	ofRunApp(window, std::make_shared<ofApp>());
	ofRunMainLoop();
}
