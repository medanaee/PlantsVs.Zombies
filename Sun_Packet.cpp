#include "Sun_Packet.hpp"

using namespace std;
using namespace sf;

Sun_Packet::Sun_Packet(string path_to_image, Vector2f pos)
{
    lilita_one.loadFromFile("./Fonts/LilitaOne.ttf");
    image.loadFromFile(path_to_image);
    sprite.setTexture(image);
    sprite.setPosition(pos);
}

Text Sun_Packet::get_money()
{
    Text money_text;
    money_text.setFont(lilita_one);
    money_text.setString(to_string(money));
    money_text.setCharacterSize(28);
    money_text.setFillColor(Color::White);
    money_text.setPosition(Vector2f(sprite.getPosition().x + 100, sprite.getPosition().y + 28));
    return money_text;
}

Sprite Sun_Packet::get_sprite()
{
    return sprite;
}

void Sun_Packet::add_money()
{
    money += 10;
}
