#pragma once
#include "Headers.hpp"
#include "Pea.hpp"
class Pea;

using namespace std;
using namespace sf;

class Zombie
{
private:

    bool is_eating = 0;
    Sprite sprite;

    int line;
    int speed;
    int initial_health;
    int health;
    int damage;
    string type;

    int pic_num = 0;
    string status = "WALKING";

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

    // Best time 0.4f
    Time interval_move = seconds(0.4f);

    // Best time 0.2f
    Time interval_frame = seconds(0.2f);

    void animation_geneartor(string pics_path, string animation_type);
    void update_animation();
    void update_position();

public:
    Zombie(int line, int speed, int health, int damage, string animations_path);
    void update();
    void change_status();
    Sprite get_sprite();
    int get_line();
    int get_health();
    void getting_hit(Pea pea);
    string get_status();
    void change_eating();
    void change_no_eating();
    int get_damage();
};