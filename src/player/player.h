#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    Player(int x, int y);
    int getX() const;
    int getY() const;
    int getHealth() const;
    int getLevel() const;
    int getExperience() const;
    int getDamage() const;
    int getExperienceThreshold() const; // Add a method to get the experience threshold

    void move(char direction);
    void takeDamage(int damage);
    void gainExperience(int amount);
    void levelUp();
    void setPosition(int x, int y); // Add the setPosition method

private:
    int x;
    int y;
    int health;
    int maxHealth; // Add an attribute for the maximum health
    int level;
    int experience;
    int damage;
    int experienceThreshold; // Add an attribute for the experience threshold
};

#endif // PLAYER_H