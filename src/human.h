#include "player.h"

class Human : public Player {
private:
    Paddle paddle;
    int direction = 0;
public:
    Human(const int startx);
    ~Human(){};
    void Update(const Ball& ball);
    void SetDirection(const int toset);
    Paddle& GetPaddle();
    Human* GenerateOffspring();
    bool IsHuman() const;
};