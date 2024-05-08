#include "Pea.hpp"

Pea::Pea(string type, Vector2f pos)
{
    if(type == "regular")
    {
        image.loadFromFile("./Pics/Main Items/Pea.png");
        sprite.setTexture(image);
    }
    else if (type == "freezed")
    {
        image.loadFromFile("./Pics/Main Items/Frozen Pea.png");
        sprite.setTexture(image);
    }
    sprite.setPosition(pos);
    sprite.scale(0.5,0.5);
    
}


void Pea::update()
{
    Time interval_move = microseconds(10);
    move_time += move_clock.restart();
    if (move_time >= interval_move)
    {
        sprite.setPosition(sprite.getPosition().x + speed, sprite.getPosition().y);
        move_time -= interval_move;
    }
    ;
}

Vector2f Pea::get_position()
{
    return sprite.getPosition();
}

Sprite Pea::get_sprite()
{
    return sprite;
}
