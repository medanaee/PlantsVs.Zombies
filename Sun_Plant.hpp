#pragma once

#include "Headers.hpp"
#include "Plant.hpp"
#include "Block.hpp"
#include "Game.hpp"

using namespace std;
using namespace sf;

class Sun_Plant : public Plant
{
private:
    std::vector<Texture> animation;
    Sprite sprite;

    

    sf::Clock frame_clock;
    sf::Time frame_time = sf::Time::Zero;

    sf::Clock generate_sun_clock;
    sf::Time generate_sun_time = sf::Time::Zero;
    
    int pic_num = 0;
    int generate_sun_speed;
public:
    Sprite get_sprite();
    void update(bool have_zombie_in_front, Game *game);
    void animation_geneartor(string pics_path);
    Sun_Plant(int health, Block *block,int generate_sun_duration);
};