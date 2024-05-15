#include "Defender_Plant.hpp"

Defender_Plant::Defender_Plant(int health, Block *block) : Plant(health,  WALLNUT, block)
{
    images();
    sprite.setTexture(perfect_helth_animation);
    this->inital_health = health;
    sprite.scale(WALLNUT_SCALE);
    //ALI
    sprite.setPosition(WALLNUT_POSITION);
}

Sprite Defender_Plant::get_sprite() { return sprite; }

void Defender_Plant::update(bool have_zombie_in_front, Game *game)
{
    if (health >= (HIGH_HEALTH_LOWER_BOUND * inital_health) && health <= (HIGH_HEALTH_UPPER_BOUND * inital_health))
        sprite.setTexture(high_helth_animation);
    if (health >= (MEDIUM_HEALTH_LOWER_BOUND * inital_health) && health <= (HIGH_HEALTH_LOWER_BOUND * inital_health))
        sprite.setTexture(medium_helth_animation);
    if (health <= (MEDIUM_HEALTH_LOWER_BOUND * inital_health))
        sprite.setTexture(low_helth_animation);
}

void Defender_Plant::images()
{
    perfect_helth_animation.loadFromFile(PERFECT_HEALTH_IMAGE);
    high_helth_animation.loadFromFile(HIGH_HEALTH_IMAGE);
    medium_helth_animation.loadFromFile(MEDIUM_HEALTH_IMAGE);
    low_helth_animation.loadFromFile(LOW_HEALTH_IMAGE);
}
