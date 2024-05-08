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

    Clock move_clock;
    Time move_time = Time::Zero;

public:
    Pea(string type);
    void update();
};

