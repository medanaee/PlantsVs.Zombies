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
    Texture FULL_helth_animation;
    Texture HASHTAD_helth_animation;
    Texture SHAAAAST_helth_animation;
    Texture CHALOOPANJ_helth_animation;

public:
    Defender_Plant(int health, Block *block);
    Sprite get_sprite();
    void update(bool have_zombie_in_front, Game* game);
    void images();
};
