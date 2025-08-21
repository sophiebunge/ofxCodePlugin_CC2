#include "tcp.h"

//--------------------------------------------------------------
TcpCommunicationManager::TcpCommunicationManager() {
	// Initialize background color as black
	bgColor = ofColor::black;
}

//--------------------------------------------------------------
TcpCommunicationManager::~TcpCommunicationManager() {
	// Cleanup is handled automatically by ofxTCPServer destructors
}

//--------------------------------------------------------------
void TcpCommunicationManager::setup() {
	// Setup the message TCP server on port 11999 to listen for incoming commands
	tcpServerMessages.setup(11999);
	// Set message delimiter so receive() knows when a message ends
	tcpServerMessages.setMessageDelimiter("\n");

	// Setup the image TCP server on port 12000 to send frames to clients
	tcpServerImages.setup(12000);

	ofLogNotice("TcpCommunicationManager") << "TCP servers initialized - Messages: 11999, Images: 12000";
}

//--------------------------------------------------------------
void TcpCommunicationManager::update() {
	// Loop over all possible client IDs connected to the message server
	for (int i = 0; i <= tcpServerMessages.getLastID(); i++) {
		if (tcpServerMessages.isClientConnected(i)) {
			// Receive a message (command) from this client (our vs code extension)
			string msg = tcpServerMessages.receive(i);

			// Process the message if it's not empty
			if (!msg.empty()) {
				processMessage(msg);
			}
		}
	}


}

//--------------------------------------------------------------
void TcpCommunicationManager::sendFrame(const ofPixels & pixels) {
	// Only send frames if there are connected clients
	if (!hasImageClients()) {
		return;
	}

	// Convert pixels to PNG format stored in an ofBuffer
	ofBuffer buffer;
	ofSaveImage(pixels, buffer, OF_IMAGE_FORMAT_PNG);

	// Get PNG image data as raw bytes (not as text)
	const char * data = buffer.getData();
	size_t dataSize = buffer.size();

	// Loop over all connected clients on the image server
	for (int i = 0; i <= tcpServerImages.getLastID(); i++) {
		if (tcpServerImages.isClientConnected(i)) {
			// Send the raw PNG bytes to the client over TCP
			tcpServerImages.sendRawBytes(i, data, dataSize);
		}
	}
}

//--------------------------------------------------------------
ofColor TcpCommunicationManager::getBackgroundColor() const {
	return bgColor;
}

//--------------------------------------------------------------
bool TcpCommunicationManager::hasImageClients() {
	// Check if any clients are connected to the image server
	for (int i = 0; i <= tcpServerImages.getLastID(); i++) {
		if (tcpServerImages.isClientConnected(i)) {
			return true;
		}
	}
	return false;
}

//--------------------------------------------------------------
void TcpCommunicationManager::processMessage(const string & message) {
	ofLogNotice("TcpCommunicationManager") << "Received message: " << message;

	// Check if the message starts with "color:" command
	if (message.find("color:") == 0) {
		// Extract the color value string after "color:"
		string colorString = message.substr(6);
		parseColorCommand(colorString);
		// Handle user typing status

	} else if (message == "coffee") {
		currentState = TamaState::Coffee;
		ofLogNotice("TcpCommunicationManager") << "Thanks for the coffee!";
	} else if (message == "sleep") {
		currentState = TamaState::Sleeping;
		ofLogNotice("TcpCommunicationManager") << "Tama is sleeping!";
	} else if (message == "fire") {
		currentState = TamaState::Fire;
		ofLogNotice("TcpCommunicationManager") << "Tama is on fire!";
	} else if (message == "sad") {
		currentState = TamaState::Sad;
		ofLogNotice("TcpCommunicationManager") << "Tama is sad!";
	} else if (message == "User started typing - sent working status") {
   if (currentState != TamaState::Timer) {
        currentState = TamaState::Working;
    }
	} else if (message == "User went idle - sent idle status") {
		  if (currentState != TamaState::Timer) {
        currentState = TamaState::Idle;
    }
	} else if (message == "timer") {
    currentState = TamaState::Timer;
    stateStartTime = ofGetElapsedTimeMillis();
    ofLogNotice("TcpCommunicationManager") << "Let's work for 20 min!";
} else if (message == "stop timer") {
    currentState = TamaState::Idle;  // or Working, up to you
    ofLogNotice("TcpCommunicationManager") << "Timer stopped manually.";
}
	// You can add more command types here in the future
	// else if (message.find("command2:") == 0) { ... }
}

//--------------------------------------------------------------
void TcpCommunicationManager::parseColorCommand(const string & colorString) {
	// Set background color based on the received command
	if (colorString == "red") {
		bgColor = ofColor::red;
	} else if (colorString == "blue") {
		bgColor = ofColor::blue;
	} else if (colorString == "green") {
		bgColor = ofColor::green;
	} else if (colorString == "yellow") {
		bgColor = ofColor::yellow;
	} else if (colorString == "magenta") {
		bgColor = ofColor::magenta;
	} else if (colorString == "cyan") {
		bgColor = ofColor::cyan;
	} else if (colorString == "white") {
		bgColor = ofColor::white;
	} else if (colorString == "black") {
		bgColor = ofColor::black;
	} else {
		ofLogWarning("TcpCommunicationManager") << "Unknown color: " << colorString;
	}

	ofLogNotice("TcpCommunicationManager") << "Background color changed to: " << colorString;
}

