#include "Zombie.hpp"



class game
{
private:
    sf::RenderWindow *window;
    sf::Event event;
    sf::Texture background_texture;
    sf::Sprite background();
    std::vector<Zombie*> zombies;
public:
    game();
    bool running();
    void render();
    void update();
    void add_zombie();
};