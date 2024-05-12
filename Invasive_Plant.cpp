#include "Invasive_Plant.hpp"

void Invasive_Plant::animation_geneartor(string pics_path, string animation_type)
{
    vector<filesystem::__cxx11::directory_entry> files;
    for (const auto &entry : filesystem::directory_iterator(pics_path + "/" + animation_type))
        if (filesystem::is_regular_file(entry.path()))
        {
            files.push_back(entry);
        }

    sort(files.begin(), files.end(), compare_files_by_name);

    for (auto &file : files)
    {
        Texture temp_pic;
        temp_pic.loadFromFile(file.path().string());
        if (animation_type == "Idle")
            idle_animation.push_back(temp_pic);
        else if (animation_type == "Attack")
            attack_animation.push_back(temp_pic);
    }
}

Sprite Invasive_Plant::get_sprite()
{
    return sprite;
}

void Invasive_Plant::update(bool has_zombie_in_line, Game *game)
{
    frame_time += frame_clock.restart();
    change_attack_time += change_attack_clock.restart();
    change_status(has_zombie_in_line);
    if (frame_time >= interval_frame)
    {
        if (status == "Idle")
        {
            sprite.setTexture(idle_animation[pic_num % idle_animation.size()]);
        }
        if (status == "Attack")
        {
            if (!shot)
                sprite.setTexture(idle_animation[pic_num % idle_animation.size()]);
            if (shot)
            {
                sprite.setTexture(attack_animation[pic_num % attack_animation.size()]);
                cout << pic_num << endl;
                if(pic_num == 8)
                    shoot(game);
                if (pic_num == attack_animation.size() - 1)
                    shot = 0;
            }
            if (change_attack_time >= interval_change_attack)
            {
                shot = 1;
                change_attack_time -= interval_change_attack;
                pic_num = -1;
            }
        }
        pic_num++;
        frame_time -= interval_frame;
    }
}

void Invasive_Plant::change_status(bool has_zombie_in_line)
{
    if (has_zombie_in_line)
        status = "Attack";
    else
        status = "Idle";
}

void Invasive_Plant::shoot(Game *game)
{
    cout << type << endl;
    if (type == "PeaShooter")
        game->add_pea("REGULAR", block->get_line(), sprite.getPosition().x + 40, 10);
    if (type == "FrozenPeaShooter")
        game->add_pea("FROZEN", block->get_line(), sprite.getPosition().x, 15);
}

Invasive_Plant::Invasive_Plant(int health, Block *block, string type) : Plant(health, type, block)
{
    if (type == "PeaShooter")
    {
        animation_geneartor("./Pics/Pea-Shooter Plant", "Idle");
        animation_geneartor("./Pics/Pea-Shooter Plant", "Attack");
    }
    else if (type == "FrozenPeaShooter")
    {
    }
    sprite.setPosition(block->get_position());
    sprite.setScale(0.18, 0.18);
}
