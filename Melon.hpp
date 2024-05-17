#pragma once
#include "Headers.hpp"
#include "Zombie.hpp"
class Zombie;

using namespace std;
using namespace sf;

class Melon
{
private:
    Texture image;
    Sprite sprite;
    int line;
    float pixel_move_x = 5;
    float initial_pixel_move_y = 10;
    float pixel_move_y;
    float delta_y_rate;
    float rotate_rate;
    int damage;

    float rotate = -70;

    Time all_time; 

    Clock move_x_clock;
    Time move_x_time = Time::Zero;
    Time interval_move_x;

    Clock move_y_clock;
    Time move_y_time = Time::Zero;
    Time interval_move_y = seconds(0.01);

    Time global_time = Time::Zero;
    Clock globa_clock;

    Time interval_target_move;
    int target_position_x;
    int target_final_pos;

    float distance;

    Zombie* target;

public:
    Melon(Zombie* target, int line, int start_x, int damage, Time all_time);
    void update();
    Sprite get_sprite();
    Zombie* get_target();
    int get_line();
    int get_damage();
};
