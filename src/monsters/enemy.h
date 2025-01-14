#ifndef ENEMY_H
#define ENEMY_H

#include <string>

class Enemy {
public:
    Enemy(int x, int y, int health, int damage, const std::string& type);
    virtual ~Enemy() = default;

    int getX() const;
    int getY() const;
    int getHealth() const;
    int getDamage() const;
    std::string getType() const;
    virtual std::string getAsciiArt() const = 0;

    void move(char direction);
    void takeDamage(int damage);

protected:
    int x;
    int y;
    int health;
    int damage;
    std::string type;
};

class Ghost : public Enemy {
public:
    Ghost(int x, int y, int health, int damage);
    std::string getAsciiArt() const override;
};

class Vampire : public Enemy {
public:
    Vampire(int x, int y, int health, int damage);
    std::string getAsciiArt() const override;
};

class Skeleton : public Enemy {
public:
    Skeleton(int x, int y, int health, int damage);
    std::string getAsciiArt() const override;
};

class Boss : public Enemy {
public:
    Boss(int x, int y, int health, int damage);
    std::string getAsciiArt() const override;
};

#endif // ENEMY_H