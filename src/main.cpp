#include "ponggame.h"

#define framerate 60

int main() {
    ofSetupOpenGL(PongAI::GetBoardWidth(), PongAI::GetBoardHeight(), OF_WINDOW); // setup the GL context
	ofSetFrameRate(framerate); // An appropriate framerate that moves the snake at a good speed
						// Due to the simple nature of our objects rendering things this slow should not cause visual discomfort or lage
	
	// this kicks off the running of my app
	ofRunApp(new PongGame());
	return 0;
}