#pragma once

#include "Headers.hpp"

using namespace std;
using namespace sf;

class Sun_Packet
{
private:
    Texture image;
    Sprite sprite;
    Font lilita_one;
    int budget = 5100;

public:
    Sun_Packet(int budget,string path_to_image, Vector2f pos);
    Text write_budget();
    Sprite get_sprite();
    void add_money(int sun_value);
    void spend_money(int sun_value);
    int get_budget();
};