#pragma once
#include "Headers.hpp"
#include "Pea.hpp"
#include "Melon.hpp"
class Pea;
class Melon;

using namespace std;
using namespace sf;

class Zombie
{
private:
    bool is_eating = false;
    bool play_die_sound = false;
    Sprite sprite;

    int line;
    int pixel_move = 10;
    int initial_health;
    int health;
    int damage;
    string type;

    int pic_num = 0;
    string status = WALK;

    vector<Texture> walk_animation;
    vector<Texture> die_animation;
    vector<Texture> eat_animation;
    vector<Texture> idle_animation;
    vector<Texture> run_animation;

    Clock frame_clock;
    Clock move_clock;
    Time frame_time = Time::Zero;
    Time move_time = Time::Zero;
    Time frozed_duration = Time::Zero;

    Time interval_move;
    Time initial_interval_move;

    Time interval_frame = ZOMBIE_ANIMATION_SPEED;

    void set_line(int line);
    void animation_geneartor_by_type(string pics_path, string animation_type);
    void animation_generator();
    void update_animation();
    void update_position();

public:
    Zombie(int line, Time interval_move, int health, int damage, string animations_path);
    void update();
    void change_status();
    Sprite get_sprite();
    int get_line();
    int get_health();
    void getting_hit(Pea pea,int cooldown);
    void getting_hit(Melon melon);
    string get_status();
    void change_eating(bool on_off);
    int get_damage();
    bool get_play_die_sound();
    Time get_interval_move();

};