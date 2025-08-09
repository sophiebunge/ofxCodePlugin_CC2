#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	// Set the window size for the openFrameworks app
	ofSetWindowShape(400, 400);

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

	// Draw the text "Tamagotchi View" at position (20, 20) inside the FBO
	ofDrawBitmapString("Tamagotchi View", 20, 20);

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
