#include "Row.hpp"

bool game::running()
{
    return window->isOpen();
}

sf::Sprite game::background()
{
    background_texture.loadFromFile("./Pics/bg.png");
    sf::Sprite background_sprite;
    background_sprite.setTexture(background_texture);
    return background_sprite;
}

game::game()
{
    window = new sf::RenderWindow(sf::VideoMode(1080, 720), "Plants vs Zombies");
}

void game::render()
{
    window->clear();
    window->draw(background());
    for(Zombie* temp : zombies)
        window->draw(temp->get_sprite());
    window->display();
}

void game::update()
{
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();
    }
    zombies[0]->update();
}

void game::add_zombie()
{
    Zombie *temp = new Zombie(1, 10, 100, "./Pics/little-zombie");
    zombies.push_back(temp);
}
