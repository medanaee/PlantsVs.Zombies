#include "Zombie.hpp"
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;
void Zombie::animation_geneartor(string pics_path, string animation_type)
{
    for (const auto &entry : fs::directory_iterator(pics_path + "/" + animation_type))
        if (fs::is_regular_file(entry.path()))
        {
            sf::Texture temp_pic;
            temp_pic.loadFromFile(entry.path().string());
            if (animation_type == "walk")
                walk_animation.push_back(temp_pic);
            else if (animation_type == "eat")
                eat_animation.push_back(temp_pic);
            else if (animation_type == "die")
                die_animation.push_back(temp_pic);
        }
}

Zombie::Zombie(int line, int speed, int health, string animations_path)
{
    this->line = line;
    this->health = health;
    this->speed = speed;
    animation_geneartor(animations_path, "walk");
    animation_geneartor(animations_path, "eat");
    animation_geneartor(animations_path, "die");
    principal_sprite.scale(0.5, 0.5);
}

void Zombie::update()
{
    sf::Time interval_frame = sf::seconds(0.2f);
    sf::Time interval_move = sf::seconds(0.8f);

    if (status == "WALKING")
    {
        frame_time += clock_frame.restart();
        if (frame_time >= interval_frame)
        {
            principal_sprite.setTexture(walk_animation[pic_num % 6]);
            frame_time -= interval_frame;
            pic_num++;
        }
    }
    if (status == "DYING")
    {
    }
    if (status == "EATING")
    {
    }

    move_time += clock_move.restart();
    if (move_time >= interval_move)
    {
        position.x += speed;
        principal_sprite.setPosition(position.x, 0);
        move_time -= interval_move;
    }
}

Sprite Zombie::get_sprite()
{
    return principal_sprite;
}