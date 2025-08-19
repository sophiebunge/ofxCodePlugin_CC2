#pragma once

#include "ofMain.h"
#include "tcp.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();

private:
	TcpCommunicationManager tcpManager; // Handles all TCP communication
	ofFbo fbo; // Framebuffer object for offscreen rendering

	string tamaText = "Hello! I'm Tama, let's get to work!";
	ofImage myImage, tamaCoffeeImage, tamaSleepImage, tamaFireImage, tamaSadImage, tamaWorkingImage;

	// Animation vars
	float tapTimer = 0.0f;
	float tapInterval = 1.0f; // new "tap" every 1.0 seconds (slower)
	int tapCount = 0;
	ofTrueTypeFont tapFont;
};