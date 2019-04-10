#pragma once

#include "ofMain.h"
#include "player.h"

class AI: public Player {
public:
    void Update();
    AI GenerateOffspring();
};