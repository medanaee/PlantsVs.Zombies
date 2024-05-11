#include "Seed_Packet.hpp"
using namespace std;
using namespace sf;

std::string float_to_string(float number)
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(1) << number;
    return oss.str();
}

Sprite Seed_Packet::get_sprite() { return sprite; }

Sprite Seed_Packet::get_plant_sprite()
{
    return plant_sprite;
}

Seed_Packet::Seed_Packet(int price, string light_path, string dark_path, string plant_image_path, Vector2f pos, Time charge_time)
{
    this->price = price;
    this->charge_time = charge_time;

    lilita_one.loadFromFile("./Fonts/LilitaOne.ttf");
    mplus1.loadFromFile("./Fonts/MPLUS.ttf");

    light_dark_images.first.loadFromFile(light_path);
    light_dark_images.second.loadFromFile(dark_path);

    plant_image.loadFromFile(plant_image_path);
    plant_sprite.setTexture(plant_image);

    sprite.setTexture(light_dark_images.second);
    sprite.setPosition(pos);

    sprite.scale(0.5, 0.5);
    plant_sprite.scale(0.18, 0.18);
}

Text Seed_Packet::get_remaining_time()
{
    Text remaning_time_text;
    remaning_time_text.setFont(mplus1);
    remaning_time_text.setCharacterSize(14);
    remaning_time_text.setFillColor(Color::White);
    remaning_time_text.setPosition(Vector2f(sprite.getPosition().x + 78, sprite.getPosition().y + 7));

    if (remaning_time != seconds(0))
        remaning_time_text.setString(float_to_string(((float)remaning_time.asSeconds())));
    else
        remaning_time_text.setString("");
    return remaning_time_text;
}

Text Seed_Packet::plant_price()
{
    Text price_text;
    price_text.setFont(lilita_one);
    price_text.setString(to_string(price));
    price_text.setCharacterSize(20);
    price_text.setFillColor(Color::White);
    price_text.setPosition(Vector2f(sprite.getPosition().x + 66, sprite.getPosition().y + 31));
    return price_text;
}

void Seed_Packet::update(int budget)
{
    if (remaning_time == seconds(0) && price <= budget)
        available = 1;
    else
        available = 0;

    if (available)
        sprite.setTexture(light_dark_images.first);
    else
        sprite.setTexture(light_dark_images.second);

    if (remaning_time != seconds(0))
    {
        time += clock.restart();
        if (time >= interval_time)
        {
            remaning_time -= interval_time;
            time -= interval_time;
        }
    }
}

void Seed_Packet::set_plant_pos(Vector2f pos)
{
    plant_sprite.setPosition(pos);
}

bool Seed_Packet::get_select()
{
    return selected;
}

void Seed_Packet::select()
{
    selected = 1;
}

void Seed_Packet::release()
{
    selected = 0;
}

bool Seed_Packet::is_avaliable()
{
    return available;
}

void Seed_Packet::reset_remaining_time()
{
    remaning_time = charge_time;
}

int Seed_Packet::get_price()
{
    return price;
}