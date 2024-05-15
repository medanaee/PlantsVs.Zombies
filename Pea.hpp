#pragma once

#include "Headers.hpp"
#include "Plant.hpp"
#include "Block.hpp"

using namespace std;
using namespace sf;

class Pea
{
private:
    Texture image;
    Sprite sprite;
    string type;
    int line;
    int speed;
    int damage;

    Clock move_clock;
    Time move_time = Time::Zero;

public:
    Pea(string type, int line ,int start_x,int damage,int speed);
    void update();
    Vector2f get_position();
    Sprite get_sprite();
    int get_line();
    int get_damage();
    string get_type(); 
};

