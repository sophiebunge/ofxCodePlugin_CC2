#pragma once

#include "ofMain.h"

class RetroGui {
public:
	// Constructor and destructor
	RetroGui();
	~RetroGui();

	// Setup the GUI with dimensions
	void setup(int width, int height);

	// Draw the GUI at specified position
	void draw(int x, int y);

	// Set the message to display
	void setMessage(const string & msg);

	// Set the background color (this will affect the GUI background too)
	void setBackgroundColor(const ofColor & color);

private:
	int guiWidth;
	int guiHeight;
	string message;
	ofColor backgroundColor;

	// Helper methods for drawing retro elements
	void drawRetroFrame(int x, int y, int w, int h);
	void drawBeveledRectangle(int x, int y, int w, int h, ofColor baseColor);
};
