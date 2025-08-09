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
};
