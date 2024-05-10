#include "Pea.hpp"

Vector2f Pea::get_position(){return sprite.getPosition();}
Sprite Pea::get_sprite(){return sprite;}
int Pea::get_line(){return line;}
int Pea::get_damage(){return damage;}
string Pea::get_type(){return type;}

Pea::Pea(string type, int line, int start_x, int damage)
{
    this->damage = damage;
    this->line = line;

    if (type == "REGULAR")
    {
        image.loadFromFile("./Pics/Main Items/Pea.png");
        sprite.setTexture(image);
    }
    else if (type == "FROZEN")
    {
        image.loadFromFile("./Pics/Main Items/Frozen Pea.png");
        sprite.setTexture(image);
    }
    //Bayad Dorost bashe badan adadi nabashe
    //define BLOCK_WIDTH 108;
    //edfine FIRST_BLOCK_DEPTH 170;
    sprite.setPosition(start_x, 170 + 108 * (line - 1));
    sprite.scale(0.5, 0.5);
}

void Pea::update()
{
    //Best time 0.01f
    Time interval_move = seconds(0.01f);
    move_time += move_clock.restart();
    if (move_time >= interval_move)
    {
        sprite.setPosition(sprite.getPosition().x + speed, sprite.getPosition().y);
        move_time -= interval_move;
    };
}