#include "Sun.hpp"

using namespace std;
using namespace sf;

class Sun_Packet
{
private:
    Texture image;
    Sprite sprite;
    Font lilita_one;
    int money = 500;

public:
    Sun_Packet(string path_to_image, Vector2f pos);
    Text get_money();
    Sprite get_sprite();
    void add_money();
};