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
#include "Setting.hpp"
#include "Headers.hpp"

using namespace std;
using namespace sf;

bool is_colliding(const Sprite &sprite1, const Sprite &sprite2);

class Game
{
private:
    Setting setting = extractor_setting();

    Seed_Packet frozen_shooter_packet;
    Seed_Packet wall_nut_packet;
    Seed_Packet shooter_packet;
    Seed_Packet sun_flower_packet;
    Seed_Packet melon_packet;
    Sun_Packet sun_packet;

    void render_packets();
    void update_packets();

    ////////////////////////////////////////////////////

    Clock global_clock;
    Time global_time = Time::Zero;

    Clock add_zombie_clock;
    Time add_zombie_time = Time::Zero;
    Time interval_add_zombie = seconds(6);

    Clock add_sun_clock;
    Time add_sun_time = Time::Zero;

    Clock add_peas_clock;
    Time add_peas_time = Time::Zero;

    Clock zombie_rate_clock;
    Time zombie_rate_time = Time::Zero;

    ////////////////////////////////////////////////////

    RenderWindow *window;
    Event event;

    Texture background_texture;
    Sprite background;

    Texture menu_texture;
    Sprite menu;

    Texture start_button_texture;
    Texture hover_start_button_texture;
    Sprite start_button;

    Texture lose_texture;
    Texture win_texture;
     
    ////////////////////////////////////////////////////

    vector<Zombie *> zombies;
    void render_line_zombies(int line);
    void render_zombies();
    void update_zombies();

    vector<Sun *> suns;
    void render_suns();
    void update_suns();

    vector<Plant *> plants;
    void rener_line_plants(int line);
    void render_plants();
    void update_plants();

    vector<Row *> table;
    void render_table();

    vector<Pea *> peas;
    void render_peas();
    void update_peas();
    void check_collision();
    void check_mouse_click();
    bool have_zombie_in_front(Plant *plant);

    string page = MENU;


    /////////////////////////////////////////////////////

    SoundBuffer main_buffer;
    SoundBuffer win_buffer;
    SoundBuffer lose_buffer;
    SoundBuffer planting_plant_buffer;
    SoundBuffer eat_plant_buffer;
    SoundBuffer die_zombie_buffer;
    SoundBuffer shoot_pea_buffer;

    Sound main_sound;
    Sound win_sound;
    Sound lose_sound;
    Sound planting_plant_sound;
    Sound eat_plant_sound;
    Sound die_zombie_sound;
    Sound shoot_pea_sound;

public:
    Game(Setting setting);
    bool running();
    void render();
    void update();
    void change_zombie_rate();
    
    void add_zombie();
    void add_plant(string type, int health, Block *block);
    
    //ALI
    void add_1zombie();
    void add_peas_test();

    void add_sun(Vector2f position);
    void add_sun_from_top();
    void add_pea(string type, int line, int start_x, int damage, int speed);
    
    vector<Row *> get_table();
    Sound *get_shoot_pea_sound();
};