#include "Melon.hpp"

Sprite Melon::get_sprite(){return sprite;}
Zombie *Melon::get_target(){return target;}
int Melon::get_line(){return line;}
int Melon::get_damage(){return damage;}

Melon::Melon(Zombie *target, int line, int start_x, int damage, Time all_time)
{
    pixel_move_y = initial_pixel_move_y;
    image.loadFromFile(MELON_ANIMATION);
    sprite.setTexture(image);
    sprite.scale(MELON_SCALE);
    sprite.setRotation(MELON_ROTATE);
    sprite.setPosition(MELON_POSITION);
    interval_target_move = target->get_interval_move();
    target_position_x = target->get_sprite().getPosition().x - ZOMBIE_DISTANSE_FROM_SPRITE;
    this->line = line;
    this->damage = damage;
    this->all_time = all_time;
    this->target = target;
    distance = target_position_x - all_time.asSeconds() * 5 / interval_target_move.asSeconds() - start_x + 180;
    interval_move_x = seconds((pixel_move_x / distance) * all_time.asSeconds());
    delta_y_rate = 2 * initial_pixel_move_y * interval_move_y.asSeconds() / all_time.asSeconds();
    rotate_rate = MELON_ALL_ROTATE * interval_move_x.asSeconds() / all_time.asSeconds();
}

void Melon::update()
{
    global_time += globa_clock.restart();
    move_x_time += move_x_clock.restart();
    if (move_x_time >= interval_move_x)
    {
        sprite.setPosition(sprite.getPosition().x + pixel_move_x, sprite.getPosition().y);
        sprite.rotate(rotate_rate);
        
        
        move_x_time -= interval_move_x;
    }

    move_y_time += move_y_clock.restart();
    if (move_y_time >= interval_move_y)
    {
        if(global_time.asSeconds() <= all_time.asSeconds()/2)
        {
            sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - pixel_move_y);
            pixel_move_y -= delta_y_rate;
        }

        if(global_time.asSeconds() > all_time.asSeconds()/2)
        {
            sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + pixel_move_y);
            pixel_move_y += delta_y_rate;
        }

        move_y_time -= interval_move_y;
    }
}
