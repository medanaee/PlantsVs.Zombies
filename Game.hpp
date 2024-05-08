#pragma once

#include "Seed_Packet.hpp"
#include "Sun_Packet.hpp"
#include "Zombie.hpp"
#include "Plant.hpp"
#include "Row.hpp"
#include "Sun.hpp"
#include "Headers.hpp"

using namespace std;
using namespace  sf;




class game
{
private:

    Seed_Packet frozen_shooter_packet;
    Seed_Packet wall_nut_packet;
    Seed_Packet shooter_packet;
    Seed_Packet sun_flower_packet;
    Seed_Packet melon_packet;
    Sun_Packet sun_packet;
    
    Clock add_zombie_clock;
    Time add_zombie_time = sf::Time::Zero;

    Clock add_sun_clock;
    Time add_sun_time = sf::Time::Zero;

    Clock global_clock;
    Time global_time = sf::Time::Zero;

    sf::RenderWindow *window;
    sf::Event event;

    sf::Texture background_texture;
    sf::Sprite background();

    std::vector<Zombie*> zombies;
    std::vector<Sun*> suns;
    std::vector<Plant*> plants;
    std::vector<Row*> table;

    


public:
    game();
    bool running();
    void render();
    void update();
    void add_zombie();
    void add_sun();
};