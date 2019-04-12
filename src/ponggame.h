#include "ofMain.h"
#include "pongai.h"

class PongGame : public ofBaseApp {
private:
    PongAI pong;
	enum GameState {RUNNING, COMPLETED};
	GameState gamestate = RUNNING;
	bool CheckForWinner();
	void DrawRunning();
	void DrawCompleted();
public:
    void setup();

	// Main event loop functions called on every frame
	void update();
	void draw();
	
	// Event driven functions, called on appropriate user action
	void keyPressed(int key);
	void keyReleased(int key);
};