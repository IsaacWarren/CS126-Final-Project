#include "ofMain.h"
#include "pongai.h"
#include "human.h"
#include "ai.h"

#include <string>
#include <random>
#include <algorithm>

class PongGame : public ofBaseApp {
private:
	const int PLAYER1X = 0;
	const int PLAYER2X = 1240;
	const int POPULATIONSIZE = 50;
	const int OFFSPRINGPERTOPPLAYER = 5;
	const int TOPPLAYERSIZE = POPULATIONSIZE / OFFSPRINGPERTOPPLAYER;
	const int SOLIDWALLGENERATIONS = 10;
	const int NEWPLAYERS = POPULATIONSIZE / 5;

	PongAI *pong;
	vector<Player*> players;
	vector<Player*> topplayers;
	enum GameState {TWOAI, MIXED, TWOHUMAN, COMPLETED, MENU, FASTTRAIN};
	GameState gamestate = MENU;
	int generation = 0;
	int match = 0;
	int humanvsaiindex = 0;
	bool solidwall = true;
	Player *human1 = new Human(PLAYER1X);
	Player *human2 = new Human(PLAYER2X);
	
	bool CheckForWinner();
	void DrawRunning();
	void DrawCompleted();
	void DrawTwoAI();
	void DrawMenu();
	void ResetTwoAI();
	void ResetWithHuman();
	void UpdateMatchGeneration();
	void RunGeneration();
	void Save();
	void Load();
	void CheckForTopPlayer(Player* player);
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