#include "ofApp.h"
#include <cstdlib>
#include <iostream>
#include <sstream>

float getCpuTemperature() {
	FILE * pipe = popen("osx-cpu-temp", "r");
	if (!pipe) return 0.0;

	char buffer[128];
	std::string result = "";
	while (fgets(buffer, sizeof buffer, pipe) != nullptr) {
		result += buffer;
	}
	pclose(pipe);

	float temp = 0.0f;
	std::stringstream ss(result);
	ss >> temp;
	return temp;
}

//--------------------------------------------------------------
void ofApp::setup() {

	tapFont.load("rainyhearts.ttf", 10); // Font for the tipitap typing

	// Set the window size for the openFrameworks app
	ofSetWindowShape(400, 400);

	// Load the image
	bool imageLoaded = myImage.load("tama_idle.png");
	tamaCoffeeImage.load("tama_idle.png");
	tamaSleepImage.load("tama_tired.png");
	tamaFireImage.load("tama_fire.png");
	tamaSadImage.load("tama_sad.png");
	tamaWorkingImage.load("tama_working.png");

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
	float temp = getCpuTemperature();
	tcpManager.systemHot = (temp > 70.0); // set threshold you like

	if (tcpManager.currentState == TamaState::Working) {
		if (ofGetElapsedTimef() - tapTimer > tapInterval) {
			tapTimer = ofGetElapsedTimef();
			tapCount++;
			if (tapCount > 3) tapCount = 0; // cycle through 0,1,2,3
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	// Begin drawing to the offscreen framebuffer object
	fbo.begin();

	// Clear previous contents (fully opaque black)
	ofClear(0, 0, 0, 255);

	// Set the background color of the FBO to the current background color from TCP manager
	ofBackground(tcpManager.getBackgroundColor());

	TamaState stateToDraw = tcpManager.currentState;

	if (tcpManager.systemHot) {
		stateToDraw = TamaState::Fire;
	}

	// Decide which image and text to show
	switch (stateToDraw) {
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
	case TamaState::Idle:
		tamaCoffeeImage.draw(0, 0, 400, 350);
		tamaText = "Hello! I'm Tama, let's get to work!";
		break;
	case TamaState::Working:
		tamaWorkingImage.draw(0, 0, 400, 350);
		tamaText = "Let's focus and get this done together!";
		// Draw "tap" text as animation
		ofSetColor(255);
		if (tapCount >= 1) tapFont.drawString("tip", 170, 155); // first tap
		if (tapCount == 2) tapFont.drawString("tap", 250, 200); // second tap
		if (tapCount == 3) tapFont.drawString("tip", 200, 220);
		ofSetColor(255); // reset color
		break;
	default:
		myImage.draw(0, 0, 400, 350);
		tamaText = "Hello! I'm Tama, let's get to work!";
		break;
	}
	ofSetColor(255); // Make sure text is white

	// Draw text always from the center of window assuming 400px width stays
	float textWidth = tamaText.length() * 8;
	float centerX = (400 - textWidth) / 2;
	ofDrawBitmapString(tamaText, centerX, 380);

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
