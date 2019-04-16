#include "ofMain.h"
#include "pongai.h"
#include "human.h"
#include "ai.h"

#include <string>
#include <random>
#include <algorithm>

class PongGame : public ofBaseApp {
private:
    PongAI *pong;
	vector<Player*> players;
	enum GameState {TWOAI, MIXED, TWOHUMAN, COMPLETED, MENU};
	GameState gamestate = TWOAI;
	int generation = 0;
	int match = 0;
	const int POPULATIONSIZE = 100;
	bool CheckForWinner();
	void DrawRunning();
	void DrawCompleted();
	void DrawTwoAI();
	void Reset();
	void UpdateMatchGeneration();
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