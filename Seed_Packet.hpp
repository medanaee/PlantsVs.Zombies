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

    Texture plant_image;
    Sprite plant_sprite;

    Time charge_time;
    Time remaning_time = seconds(0);
    Time interval_time = seconds(0.1f);
    Time time = Time::Zero;
    Clock clock;
    
    Text remaining_time_preview();
    Text price_preview();
    
    int price;
    bool selected = false;
    bool available = false;
 
    public:

    Seed_Packet(string type,int price, string light_path, string dark_path, string plant_image_path, Vector2f pos, Time charge_time);
    Sprite get_plant_sprite();
    void update(int budget);
    void show(RenderWindow *window);
    void show_preview(Vector2f pos);
    bool selection_status();
    void select();
    void release();
    bool is_avaliable();
    Sprite get_sprite();
    void reset_remaining_time();
    int cost();
};