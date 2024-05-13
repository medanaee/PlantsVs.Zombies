#pragma once
#include "Headers.hpp"

using namespace std;
using namespace sf;

class Seed_Packet
{
    private:
    pair<Texture, Texture> light_dark_images;
    Sprite sprite;
    Texture plant_image;
    Sprite plant_sprite;
    Font lilita_one;
    Font mplus1;
    Time charge_time;
    Time remaning_time = seconds(0);
    Time interval_time = seconds(0.1f);
    Time time = Time::Zero;
    Clock clock;
    int price;

    bool selected = 0;
    bool available = 0;
 
    public:
    Seed_Packet(string type,int price, string light_path, string dark_path, string plant_image_path, Vector2f pos, Time charge_time);
    Text get_remaining_time();
    Text plant_price();
    Sprite get_sprite();
    Sprite get_plant_sprite();
    void update(int budget);
    
    void set_plant_pos(Vector2f pos);
    bool get_select();
    void select();
    void release();
    bool is_avaliable();
    void reset_remaining_time();
    int get_price();
};