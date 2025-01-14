# Terminal-Dungeon

---

A little video game running in a terminal

⚠️ The exercise will be implemented in the inventory feature.

### How to run the game

---

> cd src

> build/Debug/terminal_game

### To execute after new implementations

---

> g++ -std=c++11 -c player/player.cpp -o build/Debug/player.o
> g++ -std=c++11 -c monsters/enemy.cpp -o build/Debug/enemy.o
> g++ -std=c++11 -c map/dungeon.cpp -o build/Debug/dungeon.o
> g++ -std=c++11 -c fight/fight.cpp -o build/Debug/fight.o
> g++ -std=c++11 -c menu/game.cpp -o build/Debug/game.o
> g++ -std=c++11 -c main.cpp -o build/Debug/main.o

> g++ -std=c++11 -o build/Debug/terminal_game build/Debug/main.o build/Debug/game.o build/Debug/dungeon.o build/Debug/player.o build/Debug/enemy.o build/Debug/fight.o

### Collaborators

- Lucas MEGNAN
- Camille GAYAT