#ifndef GAME_H
#define GAME_H

#include "../map/dungeon.h"
#include "../inventory-management/inventory.h"

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
    Inventory inventory; // Add inventory as a member of the Game class
};

#endif // GAME_H