#include "Plant.hpp"

string Plant::get_type(){return type;}
Block *Plant::get_block(){return block;}
int Plant::get_health(){return health;}

Plant::Plant(int health, string type, Block *block)
{
    this->block = block;
    this->health = health;
    this->type = type;
    block->put_plant(this);
}

void Plant::eaten_by(Zombie *zombie)
{
    if (find(corrosive_zombies.begin(), corrosive_zombies.end(), zombie) == corrosive_zombies.end())
        corrosive_zombies.push_back(zombie);
    Time interval_time = seconds(1);
    hit_time += hit_clock.restart();
    if (hit_time >= interval_time)
    {
        for (Zombie *temp : corrosive_zombies)
            health -= temp->get_damage();
        corrosive_zombies.clear();
        hit_time = seconds(0);
    }
}
