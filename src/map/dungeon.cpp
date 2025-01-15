#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <random>
#include <sstream>

#include "dungeon.h"
#include "../fight/fight.h"

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

    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(1, width - 2);
    std::uniform_int_distribution<> disY(1, height - 2);

    // Initialize enemies at random positions
    enemies.push_back(new Ghost(disX(gen), disY(gen), 5, 2));
    enemies.push_back(new Vampire(disX(gen), disY(gen), 10, 3));
    enemies.push_back(new Skeleton(disX(gen), disY(gen), 7, 2));
    enemies.push_back(new Ghost(disX(gen), disY(gen), 5, 2));
    enemies.push_back(new Vampire(disX(gen), disY(gen), 10, 3));
    enemies.push_back(new Skeleton(disX(gen), disY(gen), 7, 2));
    enemies.push_back(new Ghost(disX(gen), disY(gen), 5, 2));
    enemies.push_back(new Vampire(disX(gen), disY(gen), 10, 3));
    enemies.push_back(new Skeleton(disX(gen), disY(gen), 7, 2));
    enemies.push_back(new Boss(disX(gen), disY(gen), 20, 5)); // Ensure the boss is not on the same position as the player
}

void Dungeon::display() const {
    // Prepare the inventory display
    std::stringstream inventoryStream;
    Inventory inventory;
    inventory.display(inventoryStream);
    std::vector<std::string> inventoryLines;
    std::string line;
    while (std::getline(inventoryStream, line)) {
        inventoryLines.push_back(line);
    }

    // Display the dungeon and inventory side by side
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
        // Print the corresponding inventory line if it exists
        if (y < inventoryLines.size()) {
            std::cout << "  " << inventoryLines[y];
        }
        std::cout << std::endl;
    }
    // Print any remaining inventory lines
    for (int i = height; i < inventoryLines.size(); ++i) {
        std::cout << std::string(width, ' ') << "  " << inventoryLines[i] << std::endl;
    }
}

void Dungeon::movePlayer(char direction) {
    int newX = player.getX();
    int newY = player.getY();
    std::string errorMessage;

    switch (direction) {
        case 'w': --newY; break;
        case 's': ++newY; break;
        case 'a': --newX; break;
        case 'd': ++newX; break;
        default:
            errorMessage = "Invalid choice. Please try again.";
            break;
    }

    if (!isWall(newX, newY)) {
        Enemy* enemy = getEnemyAt(newX, newY);
        if (enemy) {
            player.move(direction); // Move player to the enemy's position
            combat(player, enemy);
            if (enemy->getHealth() <= 0) {
                // Remove the defeated enemy from the list
                enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());
                if (enemy->getType() == "Boss") {
                    delete enemy; // Free the memory
                    rebuildDungeon(); // Rebuild the dungeon if the Boss is defeated
                } else {
                    delete enemy; // Free the memory
                }
            }
        } else {
            player.move(direction);
        }
    } else {
        errorMessage = "You can't move through walls!";
    }

    // Display the dungeon
    display();

    // Display the error message if any
    if (!errorMessage.empty()) {
        std::cout << "=============================" << std::endl;
        std::cout << errorMessage << std::endl;
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
    int healthIncrement = loopCount * 2; // Increase the health of enemies with each loop
    int damageIncrement = loopCount; // Increase the damage of enemies with each loop

    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(1, width - 2);
    std::uniform_int_distribution<> disY(1, height - 2);

    for (int i = 0; i < numEnemies; ++i) {
        int x, y;
        do {
            x = disX(gen);
            y = disY(gen);
        } while (x == player.getX() && y == player.getY()); // Ensure enemies are not placed on the player's position

        Enemy* enemy;
        if (i % 3 == 0) {
            enemy = new Ghost(x, y, 5, 2);
        } else if (i % 3 == 1) {
            enemy = new Vampire(x, y, 10, 3);
        } else {
            enemy = new Skeleton(x, y, 7, 2);
        }
        enemy->increaseStrength(healthIncrement, damageIncrement);
        enemies.push_back(enemy);
    }

    // Add a new Boss with increased strength
    int bossX, bossY;
    do {
        bossX = disX(gen);
        bossY = disY(gen);
    } while (bossX == player.getX() && bossY == player.getY());
    Boss* boss = new Boss(bossX, bossY, 20, 5);
    boss->increaseStrength(healthIncrement * 2, damageIncrement * 2); // Boss has double the health and damage increment
    enemies.push_back(boss);
}