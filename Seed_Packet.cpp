#include "Seed_Packet.hpp"
using namespace std;
using namespace sf;

Seed_Packet::Seed_Packet(string light_path,string dark_path, Vector2f pos)
{
    lilita_one.loadFromFile("./Fonts/LilitaOne.ttf");
    mplus1.loadFromFile("./Fonts/MPLUS.ttf");
    light_dark_images.first.loadFromFile(light_path);
    light_dark_images.second.loadFromFile(dark_path);
    sprite.setTexture(light_dark_images.second);
    sprite.setPosition(pos);
    sprite.scale(0.5, 0.5);
}

Text Seed_Packet::get_remaining_time()
{
    Text remaning_time_text;
    remaning_time_text.setFont(mplus1);
    remaning_time_text.setString(to_string((int)remaning_time.asSeconds()));
    remaning_time_text.setCharacterSize(14);
    remaning_time_text.setFillColor(Color::White);
    remaning_time_text.setPosition(Vector2f(sprite.getPosition().x + 78, sprite.getPosition().y + 7));
    return remaning_time_text;
}

Text Seed_Packet::get_price()
{
    Text price_text;
    price_text.setFont(lilita_one);
    price_text.setString(to_string(price));
    price_text.setCharacterSize(20);
    price_text.setFillColor(Color::White);
    price_text.setPosition(Vector2f(sprite.getPosition().x + 66, sprite.getPosition().y + 31));
    return price_text;
}

Sprite Seed_Packet::get_sprite()
{
    return sprite;
}
