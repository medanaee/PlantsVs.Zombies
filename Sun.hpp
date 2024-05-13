#pragma once
#include "Headers.hpp"
using namespace std;
using namespace sf;

class Sun
{
private:
    Texture picture;
    Sprite sprite;
    int speed;
    Clock move_clock;
    Time move_time = Time::Zero;
    Clock remove_clock;
    Time remove_time = Time::Zero;
    string type;

public:
    Sun(float pos_x,int speed);
    Sun(Vector2f position);
    void update();
    Vector2f get_position();
    Sprite get_sprite();
    Texture get_texture();
    bool is_die();
};