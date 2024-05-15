#include "Sun.hpp"

Vector2f Sun::get_position() { return Vector2f(sprite.getPosition().x, sprite.getPosition().y); }
Sprite Sun::get_sprite() { return sprite; }
Texture Sun::get_texture() { return picture; }

bool Sun::is_die()
{
    if(type == FIX)
    {
        //ALI
        sf::Time interval_remove = sf::seconds(5);
        remove_time += remove_clock.restart();
        if (remove_time >= interval_remove)
            return true;
    }
    return false;
}

Sun::Sun(float pos_x, int speed)
{
    type = MOBILE;
    this->speed = speed;
    picture.loadFromFile(SUN_IMAGE);
    sprite.setTexture(picture);
    sprite.setPosition(pos_x, 0);
    sprite.scale(SUN_SCALE);
}

Sun::Sun(Vector2f position)
{
    type = FIX;
    picture.loadFromFile(SUN_IMAGE);
    sprite.setTexture(picture);
    sprite.setPosition(position);
    sprite.scale(SUN_SCALE);
}

void Sun::update()
{
    if(type == MOBILE)
    {
        //ALI
        sf::Time interval_move = sf::seconds(0.1f);
        move_time += move_clock.restart();
        if (move_time >= interval_move)
        {
            sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + speed);
            move_time -= interval_move;
        }
    }
    
}