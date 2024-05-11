#include "Plant.hpp"

Plant::Plant(int health, string type, Block *block)
{
    this->block = block;
    this->health = health;
    this->type = type;
    block->set_plant(this);
}

void Plant::getting_hit(Zombie* zombie)
{
    health;
}

string Plant::get_type()
{
    return type;
}
