#pragma once
#include "Headers.hpp"

using namespace std;

struct ZombieSetting
{
    string type;
    int damage;
    int health;
    int hit_rate;
    int speed;
};

struct PlantSetting
{
    string type;
    int damage;
    int health;
    int cooldown;
    int hit_rate;
    int speed;
    int price;
};

struct TimeSetting
{
    int total_time;
    int first_time_flag;
    float initial_duration_zombie_attack;
    float decrease_duration_zombie_attack;
};

struct SunSetting
{
    int vertical_speed;
    int money;
};

struct Setting
{
    vector<ZombieSetting> zombies_data;
    vector<PlantSetting> plants_data;
    TimeSetting time_data;
    SunSetting sun_data;
};

Setting setting();
