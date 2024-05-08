#pragma once

#include "Headers.hpp"
#include "Plant.hpp"

using namespace std;
using namespace sf;

class Sun_Plant : public Plant
{
private:
    std::vector<Texture> animation;
    sf::Clock frame_clock;
    sf::Time frame_time = sf::Time::Zero;
public:
    Sun_Plant();
};