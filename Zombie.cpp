#include "Zombie.hpp"
namespace fs = std::filesystem;

// Logic Function for Sort Animation-Frame by Number
bool compare_files_by_name(filesystem::__cxx11::directory_entry file1, filesystem::__cxx11::directory_entry file2)
{
    return (file1.path().filename().string() < file2.path().filename().string());
}

int Zombie::get_health(){return health;}
Sprite Zombie::get_sprite() { return sprite; }
int Zombie::get_line() { return line; }


void Zombie::getting_hit(Pea pea)
{
    health -= pea.get_damage();
    if (pea.get_type() == "FROZEN")
    {
        frozed_duration += seconds(5);
        interval_move = seconds(0.6f);
    }
}

// Generate Animations
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
        else if (animation_type == "Run")
            run_animation.push_back(temp_pic);
    }
}

// Constructor
Zombie::Zombie(int line, int speed, int health, string type)
{
    this->line = line;
    this->health = health;
    this->speed = speed;
    this->type = type;
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
        animation_geneartor("./Pics/Angry Zombie", "Run");
    }
    sprite.scale(0.5, 0.5);
    switch (line)
    {
    case 1:
        sprite.setPosition(Vector2f(500, 50));
        break;
    case 2:
        sprite.setPosition(Vector2f(500, 158));
        break;
    case 3:
        sprite.setPosition(Vector2f(500, 266));
        break;
    case 4:
        sprite.setPosition(Vector2f(500, 374));
        break;
    case 5:
        sprite.setPosition(Vector2f(500, 482));
        break;
    }
}

void Zombie::update_animation()
{
    frame_time += clock_frame.restart();
    if (frame_time >= interval_frame)
    {
        if (status == "WALKING")
            sprite.setTexture(walk_animation[pic_num % walk_animation.size()]);
        else if (status == "DYING")
            sprite.setTexture(die_animation[pic_num % die_animation.size()]);
        else if (status == "EATING")
            sprite.setTexture(eat_animation[pic_num % eat_animation.size()]);
        else if (status == "IDLE")
            sprite.setTexture(idle_animation[pic_num % idle_animation.size()]);
        else if (status == "RUNNING" && type == "angry")
            sprite.setTexture(run_animation[pic_num % run_animation.size()]);

        frame_time -= interval_frame;
        pic_num++;
    }
}

void Zombie::update_position()
{
    move_time += clock_move.restart();
    if (move_time >= interval_move && status == "WALKING")
    {
        sprite.setPosition(sprite.getPosition().x - speed, sprite.getPosition().y);
        move_time -= interval_move;
    }
}

void Zombie::update()
{
    update_animation();
    update_position();
    change_status();
}

void Zombie::change_status()
{
    // Best position for stop x==100
    if (sprite.getPosition().x <= 100)
        status = "IDLE";
    if (type == "angry" && health <= (initial_health) / 10)
        status = "RUNNING";
    if (health <= 0)
        status = "DYING";
}