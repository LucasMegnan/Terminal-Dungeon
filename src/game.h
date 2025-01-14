#ifndef GAME_H
#define GAME_H

#include "dungeon.h"

class Game {
public:
    Game();
    void start();
    bool isRunning() const;
    void update();
    void end();
    void screenMenu() const;

private:
    bool running;
    Dungeon dungeon;
};

#endif // GAME_H