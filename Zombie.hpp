#include "Sun_Packet.hpp"

class Zombie
{
private:
    Sprite sprite;
    

    int line;
    int speed;
    int health;
    string type;

    int pic_num = 0;
    string status = "WALKING";

    vector<Texture> walk_animation;
    vector<Texture> die_animation;
    vector<Texture> eat_animation;
    vector<Texture> idle_animation;

    sf::Clock clock_frame;
    sf::Clock clock_move;
    sf::Time frame_time = sf::Time::Zero;
    sf::Time move_time = sf::Time::Zero;

    void animation_geneartor(string pics_path, string animation_type);

public:
    Zombie(int line, int speed, int health, string animations_path);
    void update();
    void change_status();
    Sprite get_sprite();
    int get_line();
};