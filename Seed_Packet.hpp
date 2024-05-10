#pragma once
#include "Headers.hpp"

using namespace std;
using namespace sf;

class Seed_Packet
{
    private:
    pair<Texture, Texture> light_dark_images;
    Sprite sprite;
    Font lilita_one;
    Font mplus1;
    Time remaning_time = seconds(0);
    int price;

    public:
    Seed_Packet(int price,string light_path, string dark_path, Vector2f pos);
    Text get_remaining_time();
    Text plant_price();
    Sprite get_sprite();
    void update_image(int budget);
};