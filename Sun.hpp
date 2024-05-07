#include "Seed_Packet.hpp"
using namespace std;
using namespace sf;

class Sun
{
private:
    Texture picture;
    Sprite sprite;
    int speed = 3;
    Clock move_clock;
    Time move_time = Time::Zero;

public:
    Sun(float pos_x);
    // void delete_sun();
    void update();
    Vector2f get_position();
    Sprite get_sprite();
    Texture get_texture();
};