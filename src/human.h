#include "player.h"

class Human : public Player {
private:
    Paddle paddle;
    int direction;
public:
    Human(const int startx);
    ~Human(){};
    void Update(const ofVec2f& balposition);
    void SetDirection(const int toset);
    Paddle& GetPaddle();
};