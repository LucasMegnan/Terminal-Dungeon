#include "player.h"

Player::Player(int x, int y) : x(x), y(y), health(10), maxHealth(10), level(1), experience(0), damage(2), experienceThreshold(10) {} // Initialize the player's position, health, level, experience, damage, and experience threshold

int Player::getX() const {
    return x;
}

int Player::getY() const {
    return y;
}

int Player::getHealth() const {
    return health;
}

int Player::getLevel() const {
    return level;
}

int Player::getExperience() const {
    return experience;
}

int Player::getDamage() const {
    return damage;
}

int Player::getExperienceThreshold() const {
    return experienceThreshold;
}

void Player::move(char direction) {
    switch (direction) {
        case 'w': --y; break;
        case 's': ++y; break;
        case 'a': --x; break;
        case 'd': ++x; break;
    }
}

void Player::takeDamage(int damage) {
    health -= damage;
    if (health < 0) {
        health = 0;
    }
    if (health > maxHealth) {
        health = maxHealth;
    }
}

void Player::gainExperience(int amount) {
    experience += amount;
    if (experience >= experienceThreshold) {
        levelUp();
    }
}

void Player::levelUp() {
    level++;
    maxHealth += 5; // Example: Gain 5 max health points per level
    health = maxHealth; // Restore health to max health on level up
    damage += 1; // Example: Gain 1 damage point per level
    experience = 0; // Reset experience after leveling up
    experienceThreshold = static_cast<int>(experienceThreshold * 1.15); // Increase the experience threshold by 15%
}