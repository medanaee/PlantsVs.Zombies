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

public:
    Sun(float pos_x,int speed);
    void update();
    Vector2f get_position();
    Sprite get_sprite();
    Texture get_texture();
};