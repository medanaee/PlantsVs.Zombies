#include "Sun.hpp"

Sun::Sun(float pos_x)
{
    picture.loadFromFile("./Pics/Main Items/Sun.png");
    sprite.setTexture(picture);
    sprite.setPosition(pos_x, 0);
    sprite.scale(0.6,0.6);
}

void Sun::update()
{
    sf::Time interval_move = sf::seconds(0.1f);
    move_time += move_clock.restart();
    if(move_time >= interval_move)
    {
        sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + speed);
        move_time -= interval_move;
    }
    

}

Vector2f Sun::get_position()
{
    return Vector2f(sprite.getPosition().x, sprite.getPosition().y);
}

Sprite Sun::get_sprite()
{
    return sprite;
}

Texture Sun::get_texture()
{
    return picture;
}
