#include "Invasive_Plant.hpp"

Sprite Invasive_Plant::get_sprite() { return sprite; }

Invasive_Plant::Invasive_Plant(int health, Block *block, string type, Time interval_shoot_speed) : Plant(health, type, block)
{
    this->interval_shoot_speed = interval_shoot_speed;
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
    else if (type == MELON)
    {
        animation_geneartor("./Pics/Melon Plant", IDLE);
        animation_geneartor("./Pics/Melon Plant", ATTACK);
    }

    if(type == PEASHOOTER || type == FROZEN_PEASHOOTER)
    {
        sprite.setPosition(block->get_position());
        sprite.setScale(PEASHOOTER_SCALE);
    }
    if(type == MELON)
    {
        sprite.setPosition(block->get_position().x -60, block->get_position().y- 45);
        sprite.setScale(1.2,1.2);
    }
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
    // ALI
    if (type == PEASHOOTER)
        game->add_pea(REGULAR, block->get_line(), sprite.getPosition().x + 60, game->get_setting()->plants_data[1].damage, game->get_setting()->plants_data[1].speed);
    if (type == FROZEN_PEASHOOTER)
        game->add_pea(FROZEN, block->get_line(), sprite.getPosition().x + 60, game->get_setting()->plants_data[2].damage, game->get_setting()->plants_data[2].speed);
}

void Invasive_Plant::update(bool have_zombie_in_front, Game *game)
{
    frame_time += frame_clock.restart();
    shoot_speed_time += shoot_speed_clock.restart();
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
                {
                    shoot(game);
                    game->get_shoot_pea_sound()->play();
                }
                if (pic_num == attack_animation.size() - 1)
                    in_shotting = false;
            }
            if (shoot_speed_time >= interval_shoot_speed)
            {
                in_shotting = true;
                shoot_speed_time -= interval_shoot_speed;
                pic_num = -1;
            }
        }
        pic_num++;
        frame_time -= interval_frame;
    }
}
