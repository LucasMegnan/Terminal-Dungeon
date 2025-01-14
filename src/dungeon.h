#ifndef DUNGEON_H
#define DUNGEON_H

#include <vector>
#include <string>
#include "player.h"
#include "enemy.h"

class Dungeon {
public:
    Dungeon(int width, int height);
    void display() const;
    void movePlayer(char direction);
    Player& getPlayer();
    bool isWall(int x, int y) const;
    Enemy* getEnemyAt(int x, int y) const;
    void rebuildDungeon(); // Add a method to rebuild the dungeon

private:
    int width;
    int height;
    int loopCount; // Add a counter for the number of loops
    std::vector<std::string> map;
    Player player;
    std::vector<Enemy*> enemies;
};

#endif // DUNGEON_H