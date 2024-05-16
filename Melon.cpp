#include "Melon.hpp"

Melon::Melon(Zombie *target, int line, int start_x, int damage, Time all_time)
{
    pixel_move_y = initial_pixel_move_y;
    image.loadFromFile("./Pics/Main Items/Melon.png");
    sprite.setTexture(image);
    sprite.scale(0.4, 0.4);
    sprite.setRotation(-70);
    sprite.setPosition(start_x, 104 + 108 * (line - 1));
    interval_target_move = target->get_interval_move();
    target_position_x = target->get_sprite().getPosition().x - 69;
    this->line = line;
    this->damage = damage;
    this->all_time = all_time;
    this->target = target;
    distance = target_position_x - all_time.asSeconds() * 10 / interval_target_move.asSeconds() - start_x + 180;
    interval_move_x = seconds((pixel_move_x / distance) * all_time.asSeconds());
    kk = 2 * initial_pixel_move_y * interval_move_y.asSeconds() / all_time.asSeconds();
    bb = 140 * interval_move_x.asSeconds() / all_time.asSeconds();
}

void Melon::update()
{
    global_time += globa_clock.restart();
    move_x_time += move_x_clock.restart();
    if (move_x_time >= interval_move_x)
    {
        sprite.setPosition(sprite.getPosition().x + pixel_move_x, sprite.getPosition().y);
        sprite.rotate(bb);
        
        
        move_x_time -= interval_move_x;
    }

    move_y_time += move_y_clock.restart();
    if (move_y_time >= interval_move_y)
    {
        if(global_time.asSeconds() <= all_time.asSeconds()/2)
        {
            sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - pixel_move_y);
            pixel_move_y -= kk;
        }

        if(global_time.asSeconds() > all_time.asSeconds()/2)
        {
            sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + pixel_move_y);
            pixel_move_y += kk;
        }

        move_y_time -= interval_move_y;
    }
}

Sprite Melon::get_sprite()
{
    return sprite;
}

Zombie *Melon::get_target()
{
    return target;
}

int Melon::get_line()
{
    return line;
}

int Melon::get_damage()
{
    return damage;
}
