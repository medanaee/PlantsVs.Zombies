#include "Plant.hpp"

class Invasive_Plant : public Plant
{
private:
    vector<Texture> animation;
    sf::Clock frame_clock;
    sf::Time frame_time = sf::Time::Zero;
    

public:
    Invasive_Plant();

};



