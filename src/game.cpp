#include <iostream>
#include "game.h"

void Game::screenMenu() const {
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
}

bool Game::isRunning() const {
    return running;
}

void Game::update() {
    char input;
    // Display player health, level, experience, and experience needed for next level
    const Player& player = dungeon.getPlayer();
    std::cout << "===============================\n";
    std::cout << "Player health: " << player.getHealth() << std::endl;
    std::cout << "Player level: " << player.getLevel() << std::endl;
    std::cout << "Player experience: " << player.getExperience() << "/" << player.getExperienceThreshold() << std::endl;
    std::cout << "===============================\n";
    std::cout << "Enter move (WASD): ";
    std::cin >> std::ws; // Ignore any leading whitespace
    input = std::cin.get();

    // Clear the input buffer to ignore any additional characters
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (input == 27) { // ASCII value for Escape key
        end();
        return;
    }

    dungeon.movePlayer(input);
    dungeon.display();

    if (player.getHealth() <= 0) {
        end();
    }
}

void Game::end() {
    running = false;
    std::cout << "Game ended!" << std::endl;
}