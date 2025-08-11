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
	ofImage myImage, tamaCoffeeImage, tamaSleepImage, tamaFireImage, tamaSadImage;
};