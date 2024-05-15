#include "Sun_Plant.hpp"

Sprite Sun_Plant::get_sprite() { return sprite; }

Sun_Plant::Sun_Plant(int health, Block *block, int generate_sun_duration) : Plant(health, SUNFLOWER, block)
{
    generate_sun_speed = generate_sun_duration;
    animation_geneartor(SUNFLOWER_ANIMATION);
    sprite.setScale(SUNFLOWER_SCALE);
    sprite.setPosition(block->get_position());
}

void Sun_Plant::update(bool have_zombie_in_front, Game *game)
{
    // ALI
    Time interval_time = seconds(0.1f);
    Time interval_generate_sun = seconds(generate_sun_speed);
    
    frame_time += frame_clock.restart();
    generate_sun_time += generate_sun_clock.restart();

    if (frame_time >= interval_time)
    {
        sprite.setTexture(animation[pic_num % animation.size()]);
        pic_num++;
        frame_time -= interval_time;
    }
    if (generate_sun_time >= interval_generate_sun)
    {
        Vector2f sprite_position = sprite.getPosition();
        game->add_sun(Vector2f(FIX_SUN_POSITION));
        generate_sun_time -= interval_generate_sun;
    }
}

void Sun_Plant::animation_geneartor(string pics_path)
{
    vector<filesystem::__cxx11::directory_entry> files;
    for (const auto &entry : filesystem::directory_iterator(pics_path))
        if (filesystem::is_regular_file(entry.path()))
            files.push_back(entry);

    sort(files.begin(), files.end(), compare_files_by_name);

    for (auto &file : files)
    {
        Texture temp_pic;
        temp_pic.loadFromFile(file.path().string());
        animation.push_back(temp_pic);
    }
}
