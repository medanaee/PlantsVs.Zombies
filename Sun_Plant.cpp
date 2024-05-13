#include "Sun_Plant.hpp"

Sprite Sun_Plant::get_sprite()
{
    return sprite;
}

void Sun_Plant::update(bool have_zombie_in_front, Game* game)
{
    Time interval_time = seconds(0.1f);
    Time interval_add_sun_time = seconds(8);

    frame_time += frame_clock.restart();
    add_sun_time += add_sun_clock.restart();

    if(frame_time >= interval_time)
    {
        sprite.setTexture(animation[pic_num % animation.size()]);
        pic_num++;
        frame_time -= interval_time;
    }
    if(add_sun_time >= interval_add_sun_time)
    {
        Vector2f sprite_position=sprite.getPosition();
        game->add_sun(Vector2f(sprite_position.x+40,sprite_position.y+50));
        add_sun_time -= interval_add_sun_time;
    }
}

void Sun_Plant::animation_geneartor(string pics_path)
{
    vector<filesystem::__cxx11::directory_entry> files;
    for (const auto &entry : filesystem::directory_iterator(pics_path))
        if (filesystem::is_regular_file(entry.path()))
        {
            files.push_back(entry);
        }

    sort(files.begin(), files.end(), compare_files_by_name);

    for (auto &file : files)
    {
        Texture temp_pic;
        temp_pic.loadFromFile(file.path().string());
        animation.push_back(temp_pic);
    }
}

Sun_Plant::Sun_Plant(int health, Block *block) : Plant(health, "SunFlower", block)
{
    animation_geneartor("./Pics/SunFlower Plant");
    sprite.setScale(0.47,0.47);
    sprite.setPosition(block->get_position());
}
