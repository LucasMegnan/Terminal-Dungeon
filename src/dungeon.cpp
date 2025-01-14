#include <iostream>
#include <algorithm>
#include <cstdlib>
#include "dungeon.h"
#include "fight.h"

Dungeon::Dungeon(int width, int height) : width(width), height(height), player(width / 2, height / 2), loopCount(0) {
    // Initialize the map with empty spaces
    map.resize(height, std::string(width, ' '));

    // Example: Add some walls to the map
    for (int i = 0; i < width; ++i) {
        map[0][i] = '#';
        map[height - 1][i] = '#';
    }
    for (int i = 0; i < height; ++i) {
        map[i][0] = '#';
        map[i][width - 1] = '#';
    }

    // Initialize enemies
    enemies.push_back(new Ghost(1, 1));
    enemies.push_back(new Vampire(3, 3));
    enemies.push_back(new Skeleton(5, 5));
    enemies.push_back(new Ghost(10, 10));
    enemies.push_back(new Vampire(15, 15));
    enemies.push_back(new Skeleton(20, 20));
    enemies.push_back(new Ghost(5, 25));
    enemies.push_back(new Vampire(10, 30));
    enemies.push_back(new Skeleton(15, 35));
    enemies.push_back(new Boss(24, 12)); // Ensure the boss is not on the same position as the player
}

void Dungeon::display() const {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            bool isEnemy = false;
            for (const auto& enemy : enemies) {
                if (x == enemy->getX() && y == enemy->getY()) {
                    std::cout << "\033[31m" << enemy->getType()[0] << "\033[0m"; // Display the first letter of the enemy type in red
                    isEnemy = true;
                    break;
                }
            }
            if (!isEnemy) {
                if (x == player.getX() && y == player.getY()) {
                    std::cout << "\033[32mP\033[0m"; // Player character in green
                } else {
                    std::cout << map[y][x];
                }
            }
        }
        std::cout << std::endl;
    }
}

void Dungeon::movePlayer(char direction) {
    int newX = player.getX();
    int newY = player.getY();

    switch (direction) {
        case 'w': --newY; break;
        case 's': ++newY; break;
        case 'a': --newX; break;
        case 'd': ++newX; break;
        default:
            std::cout << "=================================" << std::endl;
            std::cout << "Invalid choice. Please try again." << std::endl;
            std::cout << "=================================" << std::endl;
            return;
    }

    if (!isWall(newX, newY)) {
        Enemy* enemy = getEnemyAt(newX, newY);
        if (enemy) {
            player.move(direction); // Move player to the enemy's position
            combat(player, enemy);
            if (enemy->getHealth() <= 0) {
                // Remove the defeated enemy from the list
                enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());
                delete enemy; // Free the memory
                if (enemy->getType() == "Boss") {
                    rebuildDungeon(); // Rebuild the dungeon if the Boss is defeated
                }
            }
        } else {
            player.move(direction);
        }
    } else {
        std::cout << "You can't move through walls!" << std::endl;
    }
}

Player& Dungeon::getPlayer() {
    return player;
}

bool Dungeon::isWall(int x, int y) const {
    return map[y][x] == '#';
}

Enemy* Dungeon::getEnemyAt(int x, int y) const {
    for (const auto& enemy : enemies) {
        if (enemy->getX() == x && enemy->getY() == y) {
            return enemy;
        }
    }
    return nullptr;
}

void Dungeon::rebuildDungeon() {
    // Clear the current enemies
    for (auto enemy : enemies) {
        delete enemy;
    }
    enemies.clear();

    // Reinitialize the map with empty spaces
    map.resize(height, std::string(width, ' '));

    // Add walls to the map
    for (int i = 0; i < width; ++i) {
        map[0][i] = '#';
        map[height - 1][i] = '#';
    }
    for (int i = 0; i < height; ++i) {
        map[i][0] = '#';
        map[i][width - 1] = '#';
    }

    // Increase the loop count
    loopCount++;

    // Initialize new enemies with increased strength
    int numEnemies = 10 + loopCount * 2; // Increase the number of enemies with each loop
    for (int i = 0; i < numEnemies; ++i) {
        int x = rand() % (width - 2) + 1;
        int y = rand() % (height - 2) + 1;
        int health = 5 + loopCount * 2; // Increase the health of enemies with each loop
        if (x == player.getX() && y == player.getY()) {
            continue; // Ensure enemies are not placed on the player's position
        }
        if (i % 3 == 0) {
            enemies.push_back(new Ghost(x, y));
        } else if (i % 3 == 1) {
            enemies.push_back(new Vampire(x, y));
        } else {
            enemies.push_back(new Skeleton(x, y));
        }
    }

    // Add a new Boss with increased strength
    int bossX, bossY;
    do {
        bossX = rand() % (width - 2) + 1;
        bossY = rand() % (height - 2) + 1;
    } while (bossX == player.getX() && bossY == player.getY());
    enemies.push_back(new Boss(bossX, bossY));
}