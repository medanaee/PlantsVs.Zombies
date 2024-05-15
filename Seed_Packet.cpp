#include "Seed_Packet.hpp"
using namespace std;
using namespace sf;

std::string float_to_string(float number)
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(1) << number;
    return oss.str();
}

void Seed_Packet::show_preview(Vector2f pos) { plant_sprite.setPosition(pos); }
bool Seed_Packet::selection_status() { return selected; }
void Seed_Packet::select() { selected = true; }
void Seed_Packet::release() { selected = false; }
bool Seed_Packet::is_avaliable() { return available; }
void Seed_Packet::reset_remaining_time() { remaning_time = charge_time; }
int Seed_Packet::cost() { return price; }
Sprite Seed_Packet::get_plant_sprite() { return plant_sprite; }
Sprite Seed_Packet::get_sprite(){return sprite;}

Seed_Packet::Seed_Packet(string type, int price, string light_path, string dark_path, string plant_image_path, Vector2f pos, Time charge_time)
{
    this->price = price;
    this->charge_time = charge_time;

    lilita_one.loadFromFile(LILITA_FONT);
    mplus1.loadFromFile(MPLUS_FONT);

    light_dark_images.first.loadFromFile(light_path);
    light_dark_images.second.loadFromFile(dark_path);

    plant_image.loadFromFile(plant_image_path);
    plant_sprite.setTexture(plant_image);

    sprite.setTexture(light_dark_images.second);
    sprite.setPosition(pos);

    sprite.scale(SEED_PACKET_SCALE);
    if (type == FROZEN_PEASHOOTER || type == PEASHOOTER)
        plant_sprite.scale(PEASHOOTER_SCALE);
    if (type == SUNFLOWER)
        plant_sprite.scale(SUNFLOWER_SCALE);
    if (type == WALLNUT)
        plant_sprite.scale(WALLNUT_SCALE);
}

Text Seed_Packet::remaining_time_preview()
{
    Text remaning_time_text;
    remaning_time_text.setFont(mplus1);
    remaning_time_text.setCharacterSize(REMAINING_TIME_TEXT_SIZE);
    remaning_time_text.setFillColor(TEXT_COLOR);
    remaning_time_text.setPosition(Vector2f(REMANING_TIME_POSITION));

    if (remaning_time != seconds(0))
        remaning_time_text.setString(float_to_string(((float)remaning_time.asSeconds())));
    else
        remaning_time_text.setString("");
    return remaning_time_text;
}

Text Seed_Packet::price_preview()
{
    Text price_text;
    price_text.setFont(lilita_one);
    price_text.setString(to_string(price));
    price_text.setCharacterSize(PRICE_TEXT_SIZE);
    price_text.setFillColor(TEXT_COLOR);
    price_text.setPosition(Vector2f(PRICE_TEXT_POSITION));
    return price_text;
}

void Seed_Packet::show(RenderWindow *window)
{
    window->draw(sprite);
    window->draw(remaining_time_preview());
    window->draw(price_preview());
}

void Seed_Packet::update(int budget)
{
    if (remaning_time == seconds(0) && price <= budget)
        available = true;
    else
        available = false;

    if (available)
        sprite.setTexture(light_dark_images.first);
    else
        sprite.setTexture(light_dark_images.second);

    time += clock.restart();
    if (time >= interval_time && remaning_time == seconds(0))
        time -= interval_time;
    if (remaning_time != seconds(0))
    {
        if (time >= interval_time)
        {
            remaning_time -= interval_time;
            time -= interval_time;
        }
    }
}