#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	// Set the window size for the openFrameworks app
	ofSetWindowShape(400, 400);

	// Load the image
	bool imageLoaded = myImage.load("tama_working.png");
	tamaCoffeeImage.load("tama_idle.png");
	tamaSleepImage.load("tama_tired.png");
	tamaFireImage.load("tama_fire.png");
	tamaSadImage.load("tama_sad.png");

	if (imageLoaded) {
		ofLogNotice("ofApp") << "Image loaded successfully! Size: "
							 << myImage.getWidth() << "x" << myImage.getHeight();
	} else {
		ofLogError("ofApp") << "Failed to load image: tama_working.png";
	}

	// Allocate the framebuffer object with width, height, and RGBA format
	fbo.allocate(400, 400, GL_RGBA);

	// Setup the TCP communication manager
	tcpManager.setup();
}

//--------------------------------------------------------------
void ofApp::update() {
	// Update the TCP communication manager to handle incoming messages
	tcpManager.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
	// Begin drawing to the offscreen framebuffer object
	fbo.begin();


	// Clear previous contents (fully opaque black)
	ofClear(0, 0, 0, 255);

	// Set the background color of the FBO to the current background color from TCP manager
	ofBackground(tcpManager.getBackgroundColor());

	// Draw the image
	

	    // Decide which image and text to show
switch (tcpManager.currentState) {
    case TamaState::Coffee:
        tamaCoffeeImage.draw(0, 0, 400, 350);
        tamaText = "Thanks for the coffee!";
        break;
    case TamaState::Sleeping:
        tamaSleepImage.draw(0, 0, 400, 350);
        tamaText = "Zzz... Tama is sleeping.";
        break;
    case TamaState::Fire:
        tamaFireImage.draw(0, 0, 400, 350);
        tamaText = "Help! I'm on fire!";
        break;
    case TamaState::Sad:
        tamaSadImage.draw(0, 0, 400, 350);
        tamaText = "Aw! Tama is sad.";
        break;
    case TamaState::Working:
    default:
        myImage.draw(0, 0, 400, 350);
        tamaText = "Hello! I'm Tama, let's get to work!";
        break;
}
	    ofSetColor(255); // Make sure text is white
	 ofDrawBitmapString(tamaText, 100, 380);
	// End drawing to the framebuffer object
	fbo.end();

	// Draw the FBO content on the main window at (0,0)
	fbo.draw(0, 0);

	// Send the current frame to connected clients (only if there are clients)
	if (tcpManager.hasImageClients()) {
		// Read the pixels from the framebuffer into an ofPixels object
		ofPixels pixels;
		fbo.readToPixels(pixels);

		// Send the frame through the TCP manager
		tcpManager.sendFrame(pixels);
	}
}
