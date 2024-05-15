#include "Invasive_Plant.hpp"

Sprite Invasive_Plant::get_sprite() { return sprite; }

Invasive_Plant::Invasive_Plant(int health, Block *block, string type, Time interval_speed) : Plant(health, type, block)
{
    this->interval_speed = interval_speed;
    if (type == PEASHOOTER)
    {
        animation_geneartor(PEASHOOTER_ANIMATION, IDLE);
        animation_geneartor(PEASHOOTER_ANIMATION, ATTACK);
    }
    else if (type == FROZEN_PEASHOOTER)
    {
        animation_geneartor(FROZEN_PEASHOOTER_ANIMATION, IDLE);
        animation_geneartor(FROZEN_PEASHOOTER_ANIMATION, ATTACK);
    }
    sprite.setPosition(block->get_position());
    sprite.setScale(PEASHOOTER_SCALE);
}

void Invasive_Plant::animation_geneartor(string pics_path, string animation_type)
{
    vector<filesystem::__cxx11::directory_entry> files;
    for (const auto &entry : filesystem::directory_iterator(pics_path + "/" + animation_type))
        if (filesystem::is_regular_file(entry.path()))
            files.push_back(entry);

    sort(files.begin(), files.end(), compare_files_by_name);

    for (auto &file : files)
    {
        Texture temp_pic;
        temp_pic.loadFromFile(file.path().string());
        if (animation_type == IDLE)
            idle_animation.push_back(temp_pic);
        else if (animation_type == ATTACK)
            attack_animation.push_back(temp_pic);
    }
}

void Invasive_Plant::change_status(bool have_zombie_in_front)
{
    if (have_zombie_in_front)
        status = ATTACK;
    else
        status = IDLE;
}

void Invasive_Plant::shoot(Game *game)
{
    if (type == PEASHOOTER)
        game->add_pea(REGULAR, block->get_line(), sprite.getPosition().x + 40, 10,6);
    if (type == FROZEN_PEASHOOTER)
        game->add_pea(FROZEN, block->get_line(), sprite.getPosition().x, 15,6);
}

void Invasive_Plant::update(bool have_zombie_in_front, Game *game)
{
    frame_time += frame_clock.restart();
    speed_time += speed_clock.restart();
    change_status(have_zombie_in_front);
    if (frame_time >= interval_frame)
    {
        if (status == IDLE)
        {
            sprite.setTexture(idle_animation[pic_num % idle_animation.size()]);
        }
        if (status == ATTACK)
        {
            if (!in_shotting)
                sprite.setTexture(idle_animation[pic_num % idle_animation.size()]);
            else
            {
                sprite.setTexture(attack_animation[pic_num % attack_animation.size()]);
                if (pic_num == 8)
                    shoot(game);
                if (pic_num == attack_animation.size() - 1)
                    in_shotting = false;
            }
            if (speed_time >= interval_speed)
            {
                in_shotting = true;
                speed_time -= interval_speed;
                pic_num = -1;
            }
        }
        pic_num++;
        frame_time -= interval_frame;
    }
}

