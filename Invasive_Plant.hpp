#pragma once

#include "Headers.hpp"
#include "Plant.hpp"
#include "Block.hpp"
#include "Game.hpp"
class Game;

using namespace std;
using namespace sf;

bool compare_files_by_name(filesystem::__cxx11::directory_entry file1, filesystem::__cxx11::directory_entry file2);

class Invasive_Plant : public Plant
{
private:
    vector<Texture> idle_animation;
    vector<Texture> attack_animation;
    Sprite sprite;

    string status = "Idle";

    sf::Clock frame_clock;
    sf::Time frame_time = sf::Time::Zero;
    Time interval_frame = seconds(0.1f);

    sf::Clock change_attack_clock;
    sf::Time change_attack_time = sf::Time::Zero;
    Time interval_change_attack = seconds(3.0f);

    int pic_num = 0;
    bool shot = 0;

public:
    Invasive_Plant(int health, Block *block, string type);
    void animation_geneartor(string pics_path, string animation_type);
    Sprite get_sprite();
    void update(bool has_zombie_in_line, Game* game);
    void change_status(bool has_zombie_in_line);
    void shoot(Game* game);
};
