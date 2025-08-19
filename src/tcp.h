#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"

enum class TamaState {
	Working,
	Coffee,
	Sleeping,
	Fire,
	Sad,
	Idle
};

class TcpCommunicationManager {
public:
	// Constructor and destructor
	TcpCommunicationManager();
	~TcpCommunicationManager();

	// Setup the TCP servers
	void setup();

	// Update method to handle incoming messages
	void update();

	// Send frame data to connected clients
	void sendFrame(const ofPixels & pixels);

	// Getter for background color (controlled by received commands)
	ofColor getBackgroundColor() const;

	// Check if there are any connected clients for image streaming
	bool hasImageClients();

	// Coffee message set up

	TamaState currentState = TamaState::Idle;
	// Track if system is hot
	bool systemHot = false;

private:
	// TCP servers
	ofxTCPServer tcpServerMessages; // Server to receive messages (commands) from VS Code
	ofxTCPServer tcpServerImages; // Server to send images (frames) to VS Code

	// Current background color based on received commands
	ofColor bgColor;

	// Helper method to process received messages
	void processMessage(const string & message);

	// Helper method to parse color commands
	void parseColorCommand(const string & colorString);

	// Handle user status if typing (Working/Idle)
	void handleUserStatus(const string & status);
};
