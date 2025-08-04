#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"
#include <map>

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();

	// void parseMessage(const std::string & msg);

	ofxTCPServer tcpServer;
	std::map<std::string, ofColor> colorMap;
	ofColor bgColor = ofColor::black;
};
