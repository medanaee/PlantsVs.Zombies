#pragma once

#include "Headers.hpp"
#include "Plant.hpp"
#include "Block.hpp"
#include "Game.hpp"

using namespace std;
using namespace sf;

class Game;

bool compare_files_by_name(filesystem::__cxx11::directory_entry file1, filesystem::__cxx11::directory_entry file2);

class Invasive_Plant : public Plant
{
private:
    vector<Texture> idle_animation;
    vector<Texture> attack_animation;
    Sprite sprite;

    string status = IDLE;

    sf::Clock frame_clock;
    sf::Time frame_time = sf::Time::Zero;
    Time interval_frame = seconds(PEA_FRAME_RATE);

    sf::Clock speed_clock;
    sf::Time speed_time = sf::Time::Zero;
    Time interval_speed;

    int pic_num = 0;
    bool in_shotting = false;

    void animation_geneartor(string pics_path, string animation_type);

public:
    Invasive_Plant(int health, Block *block, string type,Time interval_speed);
    Sprite get_sprite();
    void update(bool have_zombie_in_front, Game* game);
    void change_status(bool have_zombie_in_front);
    void shoot(Game* game);
};