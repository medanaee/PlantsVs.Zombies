#include "Plant.hpp"

Plant::Plant(int health, string type, Block *block)
{
    this->block = block;
    this->health = health;
    this->type = type;
    block->set_plant(this);
}

void Plant::getting_hit(Zombie *zombie)
{
    if (find(eating_zombies.begin(), eating_zombies.end(), zombie) == eating_zombies.end())
        eating_zombies.push_back(zombie);
    Time interval_time = seconds(1);
    hit_time += hit_clock.restart();
    if (hit_time >= interval_time)
    {
        for (Zombie *temp : eating_zombies)
            health -= temp->get_damage();
        eating_zombies.clear();
        hit_time = seconds(0);
    }
}

string Plant::get_type()
{
    return type;
}

Block *Plant::get_block()
{
    return block;
}

int Plant::get_health()
{
    return health;
}
