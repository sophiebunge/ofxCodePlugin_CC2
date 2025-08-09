#include "ofApp.h"
#include "ofxNetwork.h"

// Two separate TCP servers: one for messages, one for images
ofxTCPServer tcpServerMessages;  // Server to receive messages (commands) from VS Code
ofxTCPServer tcpServer;          // Server to send images (frames) to VS Code

ofFbo fbo;           // Framebuffer object used to draw the Tamagotchi graphics offscreen
ofColor bgColor;     // Background color for the Tamagotchi display

//--------------------------------------------------------------
void ofApp::setup() {
    // Set the window size for the openFrameworks app
    ofSetWindowShape(400, 400);

    // Allocate the framebuffer object with width, height, and RGBA format
    fbo.allocate(400, 400, GL_RGBA);

    // Setup the message TCP server on port 11999 to listen for incoming commands
    tcpServerMessages.setup(11999);
    // Set message delimiter so receive() knows when a message ends
    tcpServerMessages.setMessageDelimiter("\n");

    // Setup the image TCP server on port 12000 to send frames to clients
    tcpServer.setup(12000);
    tcpServer.setMessageDelimiter("\n");

    // Initialize the background color as black
    bgColor = ofColor::black;
}

//--------------------------------------------------------------
void ofApp::update() {
    // Loop over all possible client IDs connected to the message server
    for (int i = 0; i <= tcpServerMessages.getLastID(); i++) {
        if (tcpServerMessages.isClientConnected(i)) {
            // Receive a message (command) from this client (our vs code extension)
            string msg = tcpServerMessages.receive(i);

            // Check if the message starts with "color:" command
            if (msg.find("color:") == 0) {
                // Extract the color value string after "color:"
                string col = msg.substr(6);

                // Set background color based on the received command
                if (col == "red") bgColor = ofColor::red;
                else if (col == "blue") bgColor = ofColor::blue;
                else if (col == "green") bgColor = ofColor::green;
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    // Begin drawing to the offscreen framebuffer object
    fbo.begin();

    // Clear previous contents (fully opaque black)
    ofClear(0, 0, 0, 255);

    // Set the background color of the FBO to the current background color
    ofBackground(bgColor);

    // Draw the text "Tamagotchi View" at position (20, 20) inside the FBO
    ofDrawBitmapString("Tamagotchi View", 20, 20);

    // End drawing to the framebuffer object
    fbo.end();

    // Draw the FBO content on the main window at (0,0)
    fbo.draw(0, 0);

    // Prepare to send the current frame to all connected clients

    // Read the pixels from the framebuffer into an ofPixels object
    ofPixels pixels;
    fbo.readToPixels(pixels);

    // Convert pixels to PNG format stored in an ofBuffer
    ofBuffer buffer;
    ofSaveImage(pixels, buffer, OF_IMAGE_FORMAT_PNG);

    // Get PNG image data as a string (encoded binary)
    string encoded = buffer.getText();

    // Loop over all connected clients on the image server
    for (int i = 0; i <= tcpServer.getLastID(); i++) {
        if (tcpServer.isClientConnected(i)) {
            // Send the encoded PNG image to the client over TCP
            tcpServer.send(i, encoded);
        }
    }
}
