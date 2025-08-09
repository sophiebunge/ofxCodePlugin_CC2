#include "RetroGui.h"

//--------------------------------------------------------------
RetroGui::RetroGui() {
	message = "";
	backgroundColor = ofColor::black;
	guiWidth = 400;
	guiHeight = 100;
}

//--------------------------------------------------------------
RetroGui::~RetroGui() {
	// Nothing to clean up
}

//--------------------------------------------------------------
void RetroGui::setup(int width, int height) {
	guiWidth = width;
	guiHeight = height;
}

//--------------------------------------------------------------
void RetroGui::draw(int x, int y) {
	// Draw the main background color that extends under the GUI
	ofSetColor(backgroundColor);
	ofDrawRectangle(x, y, guiWidth, guiHeight);

	// Draw the retro GUI frame
	drawRetroFrame(x, y, guiWidth, guiHeight);

	// Draw the white text bar (inset from edges)
	int barMargin = 10;
	int barHeight = 30;
	int barY = y + (guiHeight - barHeight) / 2;

	drawBeveledRectangle(x + barMargin, barY, guiWidth - (barMargin * 2), barHeight, ofColor::white);

	// Draw the text on top of the white bar
	ofSetColor(ofColor::black);
	int textX = x + barMargin + 8;
	int textY = barY + 20; // Centered vertically in the bar
	ofDrawBitmapString(message, textX, textY);
}

//--------------------------------------------------------------
void RetroGui::setMessage(const string & msg) {
	message = msg;
}

//--------------------------------------------------------------
void RetroGui::setBackgroundColor(const ofColor & color) {
	backgroundColor = color;
}

//--------------------------------------------------------------
void RetroGui::drawRetroFrame(int x, int y, int w, int h) {
	// Draw outer dark border (retro style)
	ofSetColor(80, 80, 80); // Dark gray
	ofSetLineWidth(2);
	ofNoFill();
	ofDrawRectangle(x + 1, y + 1, w - 2, h - 2);

	// Draw inner light border (classic bevel effect)
	ofSetColor(200, 200, 200); // Light gray
	ofSetLineWidth(1);
	// Top and left lines (highlight)
	ofDrawLine(x + 2, y + 2, x + w - 3, y + 2); // Top
	ofDrawLine(x + 2, y + 2, x + 2, y + h - 3); // Left

	// Bottom and right lines (shadow)
	ofSetColor(120, 120, 120); // Medium gray
	ofDrawLine(x + 3, y + h - 3, x + w - 3, y + h - 3); // Bottom
	ofDrawLine(x + w - 3, y + 3, x + w - 3, y + h - 3); // Right
}

//--------------------------------------------------------------
void RetroGui::drawBeveledRectangle(int x, int y, int w, int h, ofColor baseColor) {
	// Fill the main rectangle
	ofSetColor(baseColor);
	ofFill();
	ofDrawRectangle(x, y, w, h);

	// Draw beveled edges for 3D effect
	ofNoFill();
	ofSetLineWidth(1);

	// Light edges (top and left)
	ofSetColor(255, 255, 255); // White highlight
	ofDrawLine(x, y, x + w - 1, y); // Top
	ofDrawLine(x, y, x, y + h - 1); // Left

	// Dark edges (bottom and right)
	ofSetColor(180, 180, 180); // Gray shadow
	ofDrawLine(x + 1, y + h - 1, x + w - 1, y + h - 1); // Bottom
	ofDrawLine(x + w - 1, y + 1, x + w - 1, y + h - 1); // Right
}
