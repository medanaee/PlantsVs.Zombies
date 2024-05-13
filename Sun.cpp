#include "Sun.hpp"

Vector2f Sun::get_position() { return Vector2f(sprite.getPosition().x, sprite.getPosition().y); }
Sprite Sun::get_sprite() { return sprite; }
Texture Sun::get_texture() { return picture; }

bool Sun::is_die()
{
    if(type == "fixed")
    {
        sf::Time interval_remove = sf::seconds(5);
        remove_time += remove_clock.restart();
        if (remove_time >= interval_remove)
        {
            return 1;
        }
    }
    return 0;
}

Sun::Sun(float pos_x, int speed)
{
    type = "moving";
    this->speed = speed;
    picture.loadFromFile("./Pics/Main Items/Sun.png");
    sprite.setTexture(picture);
    sprite.setPosition(pos_x, 0);
    sprite.scale(0.6, 0.6);
}

Sun::Sun(Vector2f position)
{
    type = "fixed";
    picture.loadFromFile("./Pics/Main Items/Sun.png");
    sprite.setTexture(picture);
    sprite.setPosition(position);
    sprite.scale(0.6, 0.6);
}

void Sun::update()
{
    if(type == "moving")
    {
        sf::Time interval_move = sf::seconds(0.1f);
        move_time += move_clock.restart();
        if (move_time >= interval_move)
        {
            sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + speed);
            move_time -= interval_move;
        }
    }
    
}