#include "ofApp.h"
#include "ofMain.h"


//========================================================================
int main() {

	//Use ofGLFWWindowSettings for more options like multi-monitor fullscreen
	ofGLWindowSettings settings;
	settings.setSize(100, 100);
	settings.setPosition(ofVec2f(-5000, -5000)); // move off-screen
	settings.windowMode = OF_WINDOW;

	auto window = ofCreateWindow(settings);
	window->setWindowShape(1, 1);
	ofRunApp(window, std::make_shared<ofApp>());
	ofRunMainLoop();
}
