#include "Zombie.hpp"
namespace fs = std::filesystem;

bool compare_files_by_name(filesystem::__cxx11::directory_entry file1, filesystem::__cxx11::directory_entry file2)
{
    return (file1.path().filename().string() < file2.path().filename().string());
}


void Zombie::animation_geneartor(string pics_path, string animation_type)
{
    vector<filesystem::__cxx11::directory_entry> files;
    for (const auto &entry : fs::directory_iterator(pics_path + "/" + animation_type))
        if (fs::is_regular_file(entry.path()))
        {
            files.push_back(entry);
        }
    sort(files.begin(), files.end(), compare_files_by_name);
    for (auto &file : files)
    {
        Texture temp_pic;
        temp_pic.loadFromFile(file.path().string());
        if (animation_type == "Walk")
            walk_animation.push_back(temp_pic);
        else if (animation_type == "Eat")
            eat_animation.push_back(temp_pic);
        else if (animation_type == "Die")
            die_animation.push_back(temp_pic);
        else if (animation_type == "Idle")
            idle_animation.push_back(temp_pic);
    }
}

Zombie::Zombie(int line, int speed, int health, string type)
{
    this->line = line;
    this->health = health;
    this->speed = speed;
    if (type == "regular")
    {
        animation_geneartor("./Pics/Regular Zombie", "Walk");
        animation_geneartor("./Pics/Regular Zombie", "Eat");
        animation_geneartor("./Pics/Regular Zombie", "Die");
        animation_geneartor("./Pics/Regular Zombie", "Idle");
    }
    if (type == "angry")
    {
        animation_geneartor("./Pics/Angry Zombie", "Walk");
        animation_geneartor("./Pics/Angry Zombie", "Eat");
        animation_geneartor("./Pics/Angry Zombie", "Die");
        animation_geneartor("./Pics/Angry Zombie", "Idle");
    }
    sprite.scale(0.5, 0.5);
    switch (line)
    {
    case 1:
        sprite.setPosition(Vector2f(980, 50));
        break;
    case 2:
        sprite.setPosition(Vector2f(980, 158));
        break;
    case 3:
        sprite.setPosition(Vector2f(980, 266));
        break;
    case 4:
        sprite.setPosition(Vector2f(980, 374));
        break;
    case 5:
        sprite.setPosition(Vector2f(980, 482));
        break;
    }
}

void Zombie::update()
{
    Time interval_frame = seconds(0.2f);
    Time interval_move = seconds(0.8f);

    if (status == "WALKING")
    {
        frame_time += clock_frame.restart();
        if (frame_time >= interval_frame)
        {
            sprite.setTexture(walk_animation[pic_num % walk_animation.size()]);
            frame_time -= interval_frame;
            pic_num++;
        }
    }
    if (status == "DYING")
    {
        frame_time += clock_frame.restart();
        if (frame_time >= interval_frame)
        {
            sprite.setTexture(die_animation[pic_num % die_animation.size()]);
            frame_time -= interval_frame;
            pic_num++;
        }
    }
    if (status == "EATING")
    {
        frame_time += clock_frame.restart();
        if (frame_time >= interval_frame)
        {
            sprite.setTexture(eat_animation[pic_num % eat_animation.size()]);
            frame_time -= interval_frame;
            pic_num++;
        }
    }
    if (status == "IDLE")
    {
        frame_time += clock_frame.restart();
        if (frame_time >= interval_frame)
        {
            sprite.setTexture(idle_animation[pic_num % (idle_animation.size())]);
            frame_time -= interval_frame;
            pic_num++;
        }
    }

    move_time += clock_move.restart();
    if (move_time >= interval_move && status == "WALKING")
    {
        sprite.setPosition(sprite.getPosition().x - speed, sprite.getPosition().y);
        move_time -= interval_move;
    }

    change_status();
}

void Zombie::change_status()
{
    if (sprite.getPosition().x <= 150)
    {
        status = "IDLE";
    }
}

Sprite Zombie::get_sprite()
{
    return sprite;
}

int Zombie::get_line()
{
    return line;
}
