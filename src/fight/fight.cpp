#include <iostream>
#include "fight.h"

void combat(Player& player, Enemy* enemy) {
    std::cout << "Combat started with " << enemy->getType() << "!" << std::endl;
    std::cout << enemy->getAsciiArt() << std::endl;

    while (player.getHealth() > 0 && enemy->getHealth() > 0) {
        std::cout << "=================================" << std::endl;
        std::cout << "Choose your action:\n1. Attack\n2. Special Attack\n3. Block\n4. Heal\n";
        std::cout << "=================================" << std::endl;
        int choice;
        std::cin >> choice;

        // Check if the input is valid
        if (std::cin.fail() || choice < 1 || choice > 4) {
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the input
            std::cout << "=================================" << std::endl;
            std::cout << "Invalid choice. Please try again." << std::endl;
            std::cout << "=================================" << std::endl;
            continue;
        }

        switch (choice) {
            case 1:
                enemy->takeDamage(player.getDamage()); // Use player's damage value
                std::cout << "You hit the " << enemy->getType() << " for " << player.getDamage() << " damage. Enemy have " << enemy->getHealth() << "HP" << std::endl;
                break;
            case 2:
                enemy->takeDamage(player.getDamage() * 2); // Example special attack damage value
                std::cout << "You hit the " << enemy->getType() << " with a special attack for " << player.getDamage() * 2 << " damage. Enemy health: " << enemy->getHealth() << std::endl;
                break;
            case 3:
                std::cout << "You block the next attack." << std::endl;
                break;
            case 4:
                player.takeDamage(-3); // Example heal value (negative damage)
                std::cout << "You heal yourself for 3 health. Your health: " << player.getHealth() << std::endl;
                break;
        }

        if (enemy->getHealth() <= 0) {
            std::cout << "You defeated the " << enemy->getType() << "!" << std::endl;
            player.gainExperience(10); // Example experience value
            std::cout << "You gained 10 experience points. Your level: " << player.getLevel() << ", Your health: " << player.getHealth() << ", Your damage: " << player.getDamage() << std::endl;
            break;
        }

        // Enemy attacks
        if (choice != 3) { // If player didn't block
            player.takeDamage(1); // Example damage value
            std::cout << "The " << enemy->getType() << " hits you for 1 damage. Your health: " << player.getHealth() << std::endl;
        } else {
            std::cout << "You blocked the attack!" << std::endl;
        }

        if (player.getHealth() <= 0) {
            std::cout << "You were defeated by the " << enemy->getType() << "!" << std::endl;
            break;
        }
    }
}