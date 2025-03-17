#ifndef DUNGEON_H
#define DUNGEON_H

#include <vector>
#include <string>
#include <sstream>
#include "../player/player.h"
#include "../monsters/enemy.h"

class Dungeon {
public:
    Dungeon(int width, int height);
    void display(std::ostream& os) const;
    void movePlayer(char direction);
    Player& getPlayer();
    bool isWall(int x, int y) const;
    Enemy* getEnemyAt(int x, int y) const;
    void rebuildDungeon();

private:
    int width;
    int height;
    int loopCount; // loopCount to track the number of loops
    std::vector<std::string> map;
    Player player;
    std::vector<Enemy*> enemies;
};

#endif // DUNGEON_H