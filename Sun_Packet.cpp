#include "Sun_Packet.hpp"

using namespace std;
using namespace sf;

Sun_Packet::Sun_Packet(int budget, string path_to_image, Vector2f pos)
{
    this->budget = budget;
    lilita_one.loadFromFile(LILITA_FONT);
    image.loadFromFile(path_to_image);
    sprite.setTexture(image);
    sprite.setPosition(pos);
}

Text Sun_Packet::budget_preview()
{
    Text money_text;
    money_text.setFont(lilita_one);
    money_text.setString(to_string(budget));
    money_text.setCharacterSize(BUDGET_TEXT_SIZE);
    money_text.setFillColor(Color::White);
    money_text.setPosition(Vector2f(BUDGET_POSITION));
    return money_text;
}

void Sun_Packet::add_money(int sun_value) { budget += sun_value; }
void Sun_Packet::spend_money(int sun_value){budget -= sun_value;}
//ALI
int Sun_Packet::get_budget() { return budget; }


void Sun_Packet::show(RenderWindow *window)
{
    window->draw(sprite);
    window->draw(budget_preview());
}