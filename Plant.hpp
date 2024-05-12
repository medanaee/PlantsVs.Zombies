#pragma once

#include "Headers.hpp"
#include "Block.hpp"
class Block;
class Zombie;
class Game;

using namespace std;
using namespace sf;

class Plant
{
protected:

    int health;
    string type;
    Block *block;
    int line;

public:
    Plant(int health, string type, Block *block);
    virtual void getting_hit(Zombie* zombie);
    virtual void update(bool has_zombie_in_line, Game* game) = 0;
    // virtual void update(bool has_zombie_in_line) = 0;
    virtual Sprite get_sprite() = 0;
    virtual string get_type();

};