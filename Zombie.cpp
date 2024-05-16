#include "Zombie.hpp"

namespace fs = std::filesystem;

bool compare_files_by_name(filesystem::__cxx11::directory_entry file1, filesystem::__cxx11::directory_entry file2) { return (file1.path().filename().string() < file2.path().filename().string()); }

int Zombie::get_health() { return health; }
Sprite Zombie::get_sprite() { return sprite; }
int Zombie::get_line() { return line; }
string Zombie::get_status() { return status; }
void Zombie::change_eating(bool on_off) { on_off == true ? is_eating = true : is_eating = false; }
int Zombie::get_damage() { return damage; }

bool Zombie::get_play_die_sound()
{
    return play_die_sound;
}

Time Zombie::get_interval_move()
{
    return interval_move;
}

void Zombie::set_line(int line)
{
    switch (line)
    {
    case 1:
        sprite.setPosition(LINE_ONE_START_POSITION);
        break;
    case 2:
        sprite.setPosition(LINE_TOW_START_POSITION);
        break;
    case 3:
        sprite.setPosition(LINE_THREE_START_POSITION);
        break;
    case 4:
        sprite.setPosition(LINE_FOUR_START_POSITION);
        break;
    case 5:
        sprite.setPosition(LINE_FIVE_START_POSITION);
        break;
    }
}

void Zombie::animation_geneartor_by_type(string pics_path, string animation_type)
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
        if (animation_type == WALK)
            walk_animation.push_back(temp_pic);
        else if (animation_type == EAT)
            eat_animation.push_back(temp_pic);
        else if (animation_type == DIE)
            die_animation.push_back(temp_pic);
        else if (animation_type == IDLE)
            idle_animation.push_back(temp_pic);
        else if (animation_type == RUN)
            run_animation.push_back(temp_pic);
    }
}

void Zombie::animation_generator()
{
    if (type == REGULAR)
    {
        animation_geneartor_by_type(REGULAR_ZOMBIE_ANIMATION, WALK);
        animation_geneartor_by_type(REGULAR_ZOMBIE_ANIMATION, EAT);
        animation_geneartor_by_type(REGULAR_ZOMBIE_ANIMATION, DIE);
        animation_geneartor_by_type(REGULAR_ZOMBIE_ANIMATION, IDLE);
    }
    if (type == ANGRY)
    {
        animation_geneartor_by_type(ANGRY_ZOMBIE_ANIMATION, WALK);
        animation_geneartor_by_type(ANGRY_ZOMBIE_ANIMATION, EAT);
        animation_geneartor_by_type(ANGRY_ZOMBIE_ANIMATION, DIE);
        animation_geneartor_by_type(ANGRY_ZOMBIE_ANIMATION, IDLE);
        animation_geneartor_by_type(ANGRY_ZOMBIE_ANIMATION, RUN);
    }
}

Zombie::Zombie(int line, Time interval_move, int health, int damage, string type)
{

    this->line = line;
    this->health = health;
    this->initial_health = health;
    this->interval_move = interval_move;
    this->initial_interval_move = interval_move;
    this->type = type;
    this->damage = damage;
    animation_generator();
    set_line(line);
    sprite.scale(ZOMBIE_SCALE);
    
}

void Zombie::update_animation()
{
    frame_time += frame_clock.restart();
    if (frame_time >= interval_frame)
    {
        if (status == WALK)
            sprite.setTexture(walk_animation[pic_num % walk_animation.size()]);
        else if (status == DYING)
        {
            sprite.setTexture(die_animation[pic_num % die_animation.size()]);
            if(pic_num == 3)
                play_die_sound = 1;
            else
                play_die_sound = 0;
            if (pic_num == 8)
                status = DIE;
        }
        else if (status == EAT)
            sprite.setTexture(eat_animation[pic_num % eat_animation.size()]);
        else if (status == IDLE)
            sprite.setTexture(idle_animation[pic_num % idle_animation.size()]);
        else if (status == RUN && type == ANGRY)
            sprite.setTexture(run_animation[pic_num % run_animation.size()]);

        if (frozed_duration.asSeconds() > 0)
            frozed_duration -= interval_frame;
        else
            interval_move = initial_interval_move;

        frame_time -= interval_frame;
        pic_num++;
    }
    
}

void Zombie::update_position()
{
    move_time += move_clock.restart();
    if (move_time >= interval_move && (status == WALK || status == RUN))
    {
        sprite.setPosition(sprite.getPosition().x - pixel_move, sprite.getPosition().y);
        move_time = seconds(0);
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
    if (sprite.getPosition().x <= HOUSE_BORDER && !is_eating)
        status = IDLE;
    if (type == ANGRY && health <= (initial_health) / 3 && status != DIE && status != DYING && status != IDLE && !is_eating)
    {
        status = RUN;
        interval_move = seconds(0.1f);
    }
    if (health <= 0 && status != DIE && status != DYING && status != IDLE)
    {
        status = DYING;
        pic_num = 0;
    }
    if (is_eating && health > 0)
        status = EAT;
    if (status == EAT && !is_eating && !(sprite.getPosition().x <= HOUSE_BORDER) && !(type == ANGRY && health <= (initial_health) / 3) && !(health <= 0))
        status = WALK;
}

void Zombie::getting_hit(Pea pea,int cooldown)
{
    health -= pea.get_damage();
    if (pea.get_type() == FROZEN)
    {
        if (frozed_duration == seconds(0))
            interval_move = seconds(cooldown * interval_move.asSeconds());
        frozed_duration += seconds(5);
    }
}

void Zombie::getting_hit(Melon melon)
{
    health -= melon.get_damage();
}
