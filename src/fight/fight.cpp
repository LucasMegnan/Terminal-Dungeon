#include <iostream>
#include <limits>
#include <termios.h>
#include <unistd.h>
#include "fight.h"
#include "../utils/utils.h"

void combat(Player& player, Enemy* enemy) {
    char choice;
    std::string messageBuffer;
    while (player.getHealth() > 0 && enemy->getHealth() > 0) {
        // Clear the screen and move the cursor to the top-left corner
        std::cout << "\033[2J\033[H";

        // Display ASCII art
        std::cout << enemy->getAsciiArt() << std::endl;

        // Display action choices
        std::cout << "=================================" << std::endl;
        std::cout << "Choose your action:\n1. Attack\n2. Special Attack\n3. Block\n4. Heal\n";
        std::cout << "=================================" << std::endl;

        // Display combat messages
        std::cout << messageBuffer << std::endl;

        choice = getch(); // Capture the key press directly

        // Display combat text
        switch (choice) {
            case '1':
                enemy->takeDamage(player.getDamage()); // Use player's damage value
                messageBuffer = "You hit the " + enemy->getType() + " for " + std::to_string(player.getDamage()) + " damage. Enemy has " + std::to_string(enemy->getHealth()) + " HP\n";
                break;
            case '2':
                enemy->takeDamage(player.getDamage() * 2); // Example special attack damage value
                messageBuffer = "You hit the " + enemy->getType() + " with a special attack for " + std::to_string(player.getDamage() * 2) + " damage. Enemy health: " + std::to_string(enemy->getHealth()) + "\n";
                break;
            case '3':
                messageBuffer = "You block the next attack.\n";
                break;
            case '4':
                player.takeDamage(-3); // Example heal value (negative damage)
                messageBuffer = "You heal yourself for 3 health. Your health: " + std::to_string(player.getHealth()) + "\n";
                break;
            default:
                messageBuffer = "Invalid choice. Please try again.\n";
                continue; // Skip the enemy's turn if the player makes an invalid choice
        }

        if (enemy->getHealth() <= 0) {
            messageBuffer += "You defeated the " + enemy->getType() + "!\n";
            player.gainExperience(10); // Example experience value
            messageBuffer += "You gained 10 experience points. Your level: " + std::to_string(player.getLevel()) + ", Your health: " + std::to_string(player.getHealth()) + ", Your damage: " + std::to_string(player.getDamage()) + "\n";
            break;
        }

        // Enemy's turn to attack
        player.takeDamage(enemy->getDamage());
        messageBuffer += "The " + enemy->getType() + " hits you for " + std::to_string(enemy->getDamage()) + " damage. Your health: " + std::to_string(player.getHealth()) + "\n";

        if (player.getHealth() <= 0) {
            messageBuffer += "You were defeated by the " + enemy->getType() + "!\n";
        }
    }
}