#include <iostream>
#include <termios.h>
#include <unistd.h>
#include "game.h"
#include "../utils/utils.h"

void Game::screenMenu() const {
    // Clear the screen and move the cursor to the top-left corner
    std::cout << "\033[2J\033[H";

    const std::string menuArt =
        " .-') _     ('-.  _  .-')  _   .-')                 .-') _    ('-.                     _ .-') _                    .-') _               ('-.                    .-') _  \n"
        "(  OO) )  _(  OO)( \\( -O )( '.( OO )_              ( OO ) )  ( OO ).-.                ( (  OO) )                  ( OO ) )            _(  OO)                  ( OO ) ) \n"
        "/     '._(,------.,------. ,--.   ,--.) ,-.-') ,--./ ,--,'   / . --. / ,--.            \\     .'_  ,--. ,--.   ,--./ ,--,'  ,----.    (,------. .-'),-----. ,--./ ,--,'  \n"
        "|'--...__)|  .---'|   /`. '|   `.'   |  |  |OO)|   \\ |  |\\   | \\-.  \\  |  |.-')        ,`'--..._) |  | |  |   |   \\ |  |\\ '  .-./-')  |  .---'( OO'  .-.  '|   \\ |  |\\  \n"
        "'--.  .--'|  |    |  /  | ||         |  |  |  \\|    \\|  | ).-'-'  |  | |  | OO )       |  |  \\  ' |  | | .-') |    \\|  | )|  |_( O- ) |  |    /   |  | |  ||    \\|  | ) \n"
        "   |  |  (|  '--. |  |_.' ||  |'.'|  |  |  |(_/|  .     |/  \\| |_.'  | |  |`-' |       |  |   ' | |  |_|( OO )|  .     |/ |  | .--, \\(|  '--. \\_) |  |\\|  ||  .     |/  \n"
        "   |  |   |  .--' |  .  '.'|  |   |  | ,|  |_.'|  |\\    |    |  .-.  |(|  '---.'       |  |   / : |  | | `-' /|  |\\    | (|  | '. (_/ |  .--'   \\ |  | |  ||  |\\    |   \n"
        "   |  |   |  `---.|  |\\  \\ |  |   |  |(_|  |   |  | \\   |    |  | |  | |      |        |  '--'  /('  '-'(_.-' |  | \\   |  |  '--'  |  |  `---.   `'  '-'  '|  | \\   |   \n"
        "   `--'   `------'`--' '--'`--'   `--'  `--'   `--'  `--'    `--' `--' `------'        `-------'   `-----'    `--'  `--'   `------'   `------'     `-----' `--'  `--'   \n";

    const std::string menuOptions =
        "===============Terminal Dungeon===============\n"
        "1. New Game\n"
        "2. Last Save\n"
        "3. Saves\n"
        "4. Exit\n"
        "==============================================\n"
        "Enter your choice: ";

    std::cout << menuArt << std::endl;
    std::cout << menuOptions << std::endl;
}

Game::Game() : running(false), dungeon(50, 25) {}

void Game::start() {
    running = true;
    std::cout << "You entered the dungeon!" << std::endl;
    dungeon.display();

    // Main game loop
    while (running) {
        update();
    }
}

bool Game::isRunning() const {
    return running;
}

void Game::update() {
    char input;
    // Clear the screen and move the cursor to the top-left corner
    system("clear");

    // Display the dungeon
    dungeon.movePlayer(input);

    // Display player health, level, experience, and experience needed for next level
    const Player& player = dungeon.getPlayer();
    std::cout << "===============================\n";
    std::cout << "Player health: " << player.getHealth() << std::endl;
    std::cout << "Player level: " << player.getLevel() << std::endl;
    std::cout << "Player experience: " << player.getExperience() << "/" << player.getExperienceThreshold() << std::endl;
    std::cout << "===============================\n";
    std::cout << "WASD to move, ESC to exit" << std::endl;
    std::cout << "===============================\n";

    input = getch(); // Capture the key press directly

    if (input == 27) { // ASCII value for Escape key
        end();
        return;
    }

    dungeon.display();

    if (player.getHealth() <= 0) {
        end();
    }
}

void Game::end() {
    running = false;
    std::cout << "Game ended!" << std::endl;
}