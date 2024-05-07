#include "Defender_Plant.hpp"

class Sun_Plant : public Plant
{
private:
    std::vector<Texture> animation;
    sf::Clock frame_clock;
    sf::Time frame_time = sf::Time::Zero;
public:
    Sun_Plant();
};