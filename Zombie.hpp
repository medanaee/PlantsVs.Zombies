#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

using namespace std;
using namespace sf;

class Zombie
{
private:
    Sprite principal_sprite;
    Vector2f position;

    int line;
    int speed;
    int health;

    int pic_num = 0;
    string status = "WALKING";

    vector<Texture> walk_animation;
    vector<Texture> die_animation;
    vector<Texture> eat_animation;

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
};