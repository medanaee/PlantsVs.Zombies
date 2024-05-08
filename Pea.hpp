#pragma once

#include "Headers.hpp"
#include "Plant.hpp"

using namespace std;
using namespace sf;

class Pea
{
private:
    Texture image;
    Sprite sprite;
    string type;
    int speed = 10;

    Clock move_clock;
    Time move_time = Time::Zero;

public:
    Pea(string type, Vector2f pos);
    void update();
    Vector2f get_position();
    Sprite get_sprite();
};

