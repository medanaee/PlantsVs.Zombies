#include "Pea.hpp"

Vector2f Pea::get_position() { return sprite.getPosition(); }
Sprite Pea::get_sprite() { return sprite; }
int Pea::get_line() { return line; }
int Pea::get_damage() { return damage; }
string Pea::get_type() { return type; }

Pea::Pea(string type, int line, int start_x, int damage, int speed)
{
    this->speed = speed;
    this->damage = damage;
    this->line = line;
    this->type = type;

    if (type == REGULAR)
        image.loadFromFile(REGULAR_PEA_IMAGE);
    else if (type == FROZEN)
        image.loadFromFile(FROZEN_PEA_IMAGE);
    sprite.setTexture(image);

    sprite.setPosition(FIRED_PEA_POSITION);
    sprite.scale(PEA_SCALE, PEA_SCALE);
}

void Pea::update()
{
    //ALI
    // Best time 0.01f
    Time interval_move = seconds(0.01f);
    move_time += move_clock.restart();
    if (move_time >= interval_move)
    {
        sprite.setPosition(sprite.getPosition().x + speed, sprite.getPosition().y);
        move_time -= interval_move;
    };
}