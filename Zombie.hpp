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
    sf::Clock clock;
    sf::Time elapsed_time = sf::Time::Zero;
    void update_status();
    void update_frame();
    void set_position(int line);
    void animation_geneartor(string pics_path,string animation_type);
public:
    Zombie(int line,int speed,int health,string animations_path);
    void eating_render();
    void dying_render();
    void moving_render();
    void update();
    Sprite get_sprite();
    ;
};