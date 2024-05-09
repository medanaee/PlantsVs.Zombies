#pragma once

#include "Seed_Packet.hpp"
#include "Sun_Packet.hpp"
#include "Zombie.hpp"
#include "Plant.hpp"
#include "Row.hpp"
#include "Sun.hpp"
#include "Pea.hpp"
#include "Headers.hpp"

using namespace std;
using namespace  sf;

bool is_colliding(const Sprite &sprite1, const Sprite &sprite2v);


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
    Time add_zombie_time = Time::Zero;

    Clock add_sun_clock;
    Time add_sun_time = Time::Zero;

    Clock global_clock;
    Time global_time = Time::Zero;

    RenderWindow *window;
    Event event;

    Texture background_texture;
    Sprite background();

    vector<Zombie*> zombies;
    vector<Sun*> suns;
    vector<Plant*> plants;
    vector<Row*> table;
    vector<Pea*> peas;


public:
    game();
    bool running();
    void render();
    void update();
    void add_zombie();
    void add_1zombie();
    void add_sun();
    void add_pea(string type, int line, int start_x);
};