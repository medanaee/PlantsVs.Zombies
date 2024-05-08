#pragma once

#include "Headers.hpp"
#include "Plant.hpp"

using namespace std;
using namespace sf;

class Defender_Plant : public Plant
{
private:

    std::vector<Texture> high_helth_animation;
    std::vector<Texture> medium_helth_animation;
    std::vector<Texture> low_helth_animation;
    sf::Clock frame_clock;
    sf::Time frame_time = sf::Time::Zero;

public:
    Defender_Plant();

};



