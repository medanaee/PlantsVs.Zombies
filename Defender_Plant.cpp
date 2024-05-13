#include "Defender_Plant.hpp"

Defender_Plant::Defender_Plant(int health, Block *block) : Plant(health, "WallNut", block)
{
    images();
    sprite.setTexture(FULL_helth_animation);
    this->inital_health = health;
    sprite.scale(0.24, 0.24);
    sprite.setPosition(block->get_position().x - 35, block->get_position().y-30);
}

Sprite Defender_Plant::get_sprite() { return sprite; }

void Defender_Plant::update(bool have_zombie_in_front, Game* game)
{
    if (health >= (0.6 * inital_health) && health <= (0.8 * inital_health))
        sprite.setTexture(HASHTAD_helth_animation);
    if (health >= (0.45 * inital_health) && health <= (0.6 * inital_health))
        sprite.setTexture(SHAAAAST_helth_animation);
    if (health <= (0.45 * inital_health))
        sprite.setTexture(CHALOOPANJ_helth_animation);
}

void Defender_Plant::images()
{
    FULL_helth_animation.loadFromFile("./Pics/Wall-Nut Plant/Full.png");
    HASHTAD_helth_animation.loadFromFile("./Pics/Wall-Nut Plant/80.png");
    SHAAAAST_helth_animation.loadFromFile("./Pics/Wall-Nut Plant/60.png");
    CHALOOPANJ_helth_animation.loadFromFile("./Pics/Wall-Nut Plant/45.png");
}
