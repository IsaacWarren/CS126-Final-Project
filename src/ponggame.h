#include "ofMain.h"
#include "pongai.h"
#include "human.h"
#include "ai.h"

class PongGame : public ofBaseApp {
private:
    PongAI *pong;
	vector<Player*> players;
	enum GameState {RUNNING, COMPLETED};
	GameState gamestate = RUNNING;
	bool CheckForWinner();
	void DrawRunning();
	void DrawCompleted();
	void Reset();
public:
    void setup();

	// Main event loop functions called on every frame
	void update();
	void draw();
	
	// Event driven functions, called on appropriate user action
	void keyPressed(int key);
	void keyReleased(int key);

	void exit();
};