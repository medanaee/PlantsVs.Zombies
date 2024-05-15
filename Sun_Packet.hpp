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
    int budget;

public:
    Sun_Packet(int budget,string path_to_image, Vector2f pos);
    Text budget_preview();
    void add_money(int sun_value);
    void spend_money(int sun_value);
    int get_budget();
    void show(RenderWindow* window);
};