#include "Setting.hpp"

using namespace std;

Setting extractor_setting()
{
    Setting set;

    ifstream file("SETTING.set");
    if (!file.is_open())
    {
        cout << "Error opening file." << endl;
    }

    string line;
    regex zombie_regex("Zombies:(\\w+)=(\\d+)-(\\d+)-([\\d.-]+)");
    regex plant_regex("Plants:(\\w+)=(\\d+)-(\\d+)-(\\d+)-(\\d+)-(\\d+)-(\\d+)");
    regex time_regex("Times:(\\d+)-([\\d.-]+)-(\\d+)-([\\d.-]+)");
    regex sun_regex("Sun:(\\d+)-(\\d+)-(\\d+)-(\\d+)");

    while (getline(file, line))
    {
        smatch match;

        if (regex_match(line, match, zombie_regex))
        {
            ZombieSetting zombie;
            zombie.type = match[1];
            zombie.damage = stoi(match[2]);
            zombie.health = stoi(match[3]);
            zombie.speed = stof(match[4]);
            set.zombies_data.push_back(zombie);
        }

        else if (regex_match(line, match, plant_regex))
        {
            PlantSetting plant;
            plant.type = match[1];
            plant.damage = stoi(match[2]);
            plant.health = stoi(match[3]);
            plant.cooldown = stoi(match[4]);
            plant.hit_rate = stoi(match[5]);
            plant.speed = stoi(match[6]);
            plant.price = stoi(match[7]);
            set.plants_data.push_back(plant);
        }

        else if (regex_match(line, match, time_regex))
        {
            set.time_data.total_time = stoi(match[1]);
            set.time_data.initial_duration_zombie_attack = stof(match[2]);
            set.time_data.time_flag = stoi(match[3]);
            set.time_data.decrease_duration_zombie_attack = stof(match[4]);
            
        }

        else if (regex_match(line, match, sun_regex))
        {
            set.sun_data.vertical_speed = stoi(match[1]);
            set.sun_data.generate_speed = stoi(match[2]);
            set.sun_data.budget = stoi(match[3]);
            set.sun_data.money = stoi(match[4]);
        }
    }
    file.close();

    return set;
}