#pragma once

#include "Seed_Packet.hpp"
#include "Sun_Packet.hpp"
#include "Zombie.hpp"
#include "Plant.hpp"
#include "Row.hpp"
#include "Sun.hpp"
#include "Pea.hpp"
#include "Invasive_Plant.hpp"
#include "Defender_Plant.hpp"
#include "Sun_Plant.hpp"
#include "Block.hpp"
#include "Headers.hpp"

using namespace std;
using namespace sf;

bool is_colliding(const Sprite &sprite1, const Sprite &sprite2);

class game
{
private:


    Seed_Packet frozen_shooter_packet;
    void render_frozen_shooter_packet();
    
    Seed_Packet wall_nut_packet;
    void render_wall_nut_packet();
    
    Seed_Packet shooter_packet;
    void render_shooter_packet();

    Seed_Packet sun_flower_packet;
    void render_sun_flower_packet();

    Seed_Packet melon_packet;
    void render_melon_packet();

    Sun_Packet sun_packet;
    void render_sun_packet();
    
    void render_packets();
    void update_packets();
    ////////////////////////////////////////////////////

    Clock global_clock;
    Time global_time = Time::Zero;
    
    Clock add_zombie_clock;
    Time add_zombie_time = Time::Zero;

    Clock add_sun_clock;
    Time add_sun_time = Time::Zero;

    Clock add_peas_clock;
    Time add_peas_time = Time::Zero;

    RenderWindow *window;
    Event event;

    Texture background_texture;
    Sprite background();

    vector<Zombie *> zombies;
    void render_line_zombies(int line);
    void render_zombies();
    void update_zombies();

    vector<Sun *> suns;
    void render_suns();
    void update_suns();

    vector<Plant *> plants;
    // void render_line_plants(int line);
    // void render_plants();
    //void update_plants();

    vector<Row *> table;
    void render_table();

    vector<Pea *> peas;
    void render_peas();
    void update_peas();
    void check_collision();
    void check_mouse_click();

public:
    game();
    bool running();
    void render();
    void update();
    void add_zombie();
    void add_1zombie();
    void add_sun();
    void add_pea(string type, int line, int start_x, int damage);
    void add_peas_test();
    void add_plant(string type, int health, Block *block);
    vector<Row *> get_table();
};