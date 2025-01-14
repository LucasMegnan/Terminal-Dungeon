#include <iostream>
#include <limits>
#include "menu/game.h"

int main()
{
    Game game;
    int choice;
    bool invalidChoice = false;

    while (true) {
        if (!invalidChoice) {
            game.screenMenu();
        }

        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the input
            std::cout << "Invalid choice. Please try again." << std::endl;
            std::cout << "Enter your choice: ";
            invalidChoice = true;
            continue;
        }

        invalidChoice = false;

        if (choice == 1) {
            game.start();

            while (game.isRunning()) {
                game.update();
            }

            game.end();
        } else if (choice == 2) {
            std::cout << "Loading last save... (not implemented yet)" << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the input
            std::cin.get(); // Wait for the user to press Enter
        } else if (choice == 3) {
            std::cout << "Displaying saves... (not implemented yet)" << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the input
            std::cin.get(); // Wait for the user to press Enter
        } else if (choice == 4) {
            std::cout << "Exiting game. Goodbye!" << std::endl;
            break;
        } else {
            invalidChoice = true;
        }
    }

    return 0;
}