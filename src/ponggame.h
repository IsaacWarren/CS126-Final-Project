#include "ofMain.h"
#include "pong.h"

class PongGame : public ofBaseApp {
private:
    Pong pong;
public:
    void setup();

	// Main event loop functions called on every frame
	void update();
	void draw();
	
	// Event driven functions, called on appropriate user action
	void keyPressed(int key);
	void keyReleased(int key);
};