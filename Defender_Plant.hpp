#pragma once

#include "Headers.hpp"
#include "Plant.hpp"
#include "Block.hpp"

using namespace std;
using namespace sf;

class Defender_Plant : public Plant
{
private:
    int inital_health;
    Sprite sprite;
    Texture perfect_helth_animation;
    Texture high_helth_animation;
    Texture medium_helth_animation;
    Texture low_helth_animation;

public:
    Defender_Plant(int health, Block *block);
    Sprite get_sprite();
    void update(bool have_zombie_in_front, Game* game);
    void images();
};