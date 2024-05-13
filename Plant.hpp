#pragma once

#include "Headers.hpp"
#include "Block.hpp"
#include "Zombie.hpp"
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
    vector<Zombie*> eating_zombies;

    Time hit_time = Time::Zero;
    Clock hit_clock;

public:
    Plant(int health, string type, Block *block);
    virtual void getting_hit(Zombie* zombie);
    virtual void update(bool have_zombie_in_front, Game* game) = 0;
    virtual Sprite get_sprite() = 0;
    virtual string get_type();
    Block* get_block();
    int get_health();

};