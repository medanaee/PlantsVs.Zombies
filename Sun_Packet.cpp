#include "Sun_Packet.hpp"

using namespace std;
using namespace sf;

Sun_Packet::Sun_Packet(int budget,string path_to_image, Vector2f pos)
{
    this->budget = budget;
    lilita_one.loadFromFile("./Fonts/LilitaOne.ttf");
    image.loadFromFile(path_to_image);
    sprite.setTexture(image);
    sprite.setPosition(pos);
}

Text Sun_Packet::write_budget()
{
    Text money_text;
    money_text.setFont(lilita_one);
    money_text.setString(to_string(budget));
    money_text.setCharacterSize(28);
    money_text.setFillColor(Color::White);
    money_text.setPosition(Vector2f(sprite.getPosition().x + 100, sprite.getPosition().y + 28));
    return money_text;
}

Sprite Sun_Packet::get_sprite() { return sprite; }
void Sun_Packet::add_money(int sun_value) { budget += sun_value; }
int Sun_Packet::get_budget() { return budget; }
