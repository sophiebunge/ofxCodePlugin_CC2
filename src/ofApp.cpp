#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	tcpServer.setup(11999);
	tcpServer.setMessageDelimiter("\n");
}

//--------------------------------------------------------------
void ofApp::update() {
	for (int i = 0; i < tcpServer.getLastID(); i++) {
		if (tcpServer.isClientConnected(i)) {

			string msg = tcpServer.receive(i);
			if (msg != "") {
				ofLog() << "Received: " << msg;
				if (msg.find("color:") == 0) {
					string col = msg.substr(6);
					if (col == "blue")
						bgColor = ofColor::blue;
					else if (col == "red")
						bgColor = ofColor::red;
					else if (col == "green")
						bgColor = ofColor::green;
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackground(bgColor);
}
