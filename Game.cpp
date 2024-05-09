#include "Game.hpp"

bool is_colliding(const Sprite &sprite1, const Sprite &sprite2)
{
    sf::FloatRect bounds1 = sprite1.getGlobalBounds();
    sf::FloatRect bounds2 = sprite2.getGlobalBounds();

    sf::FloatRect intersection;
    if (bounds1.intersects(bounds2, intersection))
    {
        int last_col = intersection.left + intersection.width;
        int start_y = intersection.top + intersection.height / 2;
        if (sprite1.getTexture()->copyToImage().getPixel((last_col - bounds1.left) * 2, (start_y - bounds1.top) * 2).a > 0)
            return true;
    }
    return false;
}

bool game::running()
{
    return window->isOpen();
}

Sprite game::background()
{
    background_texture.loadFromFile("./Pics/Main Items/Background.png");
    Sprite background_sprite;
    background_sprite.setTexture(background_texture);
    return background_sprite;
}

game::game()
    : frozen_shooter_packet("./Pics/Main Items/Seed-Packet/Frozen Pea-Shooter.png", "./Pics/Main Items/Seed-Packet/Frozen Pea-Shooter Dark.png", Vector2f(13, 243)),
      wall_nut_packet("./Pics/Main Items/Seed-Packet/Wall-Nut.png", "./Pics/Main Items/Seed-Packet/Wall-Nut Dark.png", Vector2f(13, 310)),
      shooter_packet("./Pics/Main Items/Seed-Packet/Pea-Shooter.png", "./Pics/Main Items/Seed-Packet/Pea-Shooter Dark.png", Vector2f(13, 176)),
      sun_flower_packet("./Pics/Main Items/Seed-Packet/SunFlower.png", "./Pics/Main Items/Seed-Packet/SunFlower Dark.png", Vector2f(13, 109)),
      melon_packet("./Pics/Main Items/Seed-Packet/Melon.png", "./Pics/Main Items/Seed-Packet/Melon Dark.png", Vector2f(13, 377)),
      sun_packet("./Pics/Main Items/Sun Bar.png", Vector2f(0, 12))
{
    window = new RenderWindow(VideoMode(1080, 720), "Plants VS. Zombies");
    for (int i = 0; i < 5; i++)
    {
        table.push_back(new Row(Vector2f(223, 145 + i * 108)));
    }
}

void game::render()
{
    window->clear();

    window->draw(background());

    for (Row *&temp : table)
    {
        for (int i = 0; i < 9; i++)
        {
            window->draw(temp->get_block(i)->get_area());
        }
    }

    for (Pea *temp : peas)
    {
        window->draw(temp->get_sprite());
    }

    for (Zombie *temp : zombies)
        if (temp->get_line() == 1)
            window->draw(temp->get_sprite());
    for (Zombie *temp : zombies)
        if (temp->get_line() == 2)
            window->draw(temp->get_sprite());
    for (Zombie *temp : zombies)
        if (temp->get_line() == 3)
            window->draw(temp->get_sprite());
    for (Zombie *temp : zombies)
        if (temp->get_line() == 4)
            window->draw(temp->get_sprite());
    for (Zombie *temp : zombies)
        if (temp->get_line() == 5)
            window->draw(temp->get_sprite());

    window->draw(melon_packet.get_sprite());
    window->draw(melon_packet.get_remaining_time());
    window->draw(melon_packet.get_price());

    window->draw(frozen_shooter_packet.get_sprite());
    window->draw(frozen_shooter_packet.get_remaining_time());
    window->draw(frozen_shooter_packet.get_price());

    window->draw(shooter_packet.get_sprite());
    window->draw(shooter_packet.get_remaining_time());
    window->draw(shooter_packet.get_price());

    window->draw(wall_nut_packet.get_sprite());
    window->draw(wall_nut_packet.get_remaining_time());
    window->draw(wall_nut_packet.get_price());

    window->draw(sun_flower_packet.get_sprite());
    window->draw(sun_flower_packet.get_remaining_time());
    window->draw(sun_flower_packet.get_price());

    window->draw(sun_packet.get_sprite());
    window->draw(sun_packet.get_money());

    for (Sun *temp : suns)
    {
        window->draw(temp->get_sprite());
    }

    window->display();
}

void game::update()
{
    while (window->pollEvent(event))
    {
        if (event.type == Event::Closed)
            window->close();
        else if (event.type == Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == Mouse::Left)
            {
                Vector2i mousePosition = Mouse::getPosition(*window);
                for (Sun *&temp : suns)
                    if (temp->get_sprite().getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                    {
                        delete temp;
                        suns.erase(find(suns.begin(), suns.end(), temp));
                        sun_packet.add_money();
                    }
            }
        }
        else if (event.type == Event::MouseMoved)
        {
            Vector2i mousePosition = Mouse::getPosition(*window);
            for (Row *&temp : table)
            {
                for (int i = 0; i < 9; i++)
                {
                    if (temp->get_block(i)->get_area().getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                    {
                        temp->get_block(i)->highlight_area();
                    }
                    else
                    {
                        temp->get_block(i)->reset_area_color();
                    }
                }
            }
        }
    }

    add_sun();
    // add_zombie();

    for (Zombie *temp : zombies)
        temp->update();

    for (Sun *&temp : suns)
    {
        temp->update();
        if (temp->get_position().y > window->getSize().y)
        {
            delete temp;
            suns.erase(find(suns.begin(), suns.end(), temp));
        }
    }
    for (Pea *temp : peas)
    {
        temp->update();
    }
    for (Zombie *temp_zombie : zombies)
    {
        for (Pea *temp_pea : peas)
        {
            if (is_colliding(temp_zombie->get_sprite(), temp_pea->get_sprite()) && temp_pea->get_line() == temp_zombie->get_line())
            {
                cout << "dclkvmscv" << endl;
                delete temp_pea;
                peas.erase(find(peas.begin(), peas.end(), temp_pea));
            }
        }
    }
}

void game::add_zombie()
{
    Time interval_add_zombie = seconds(3);
    add_zombie_time += add_zombie_clock.restart();
    if (add_zombie_time >= interval_add_zombie)
    {
        if (rand() % 2)
            zombies.push_back(new Zombie(random() % 5 + 1, 10, 100, "regular"));
        else
            zombies.push_back(new Zombie(rand() % 5 + 1, 10, 100, "angry"));

        add_zombie_time -= interval_add_zombie;
    }
}

void game::add_1zombie()
{

    if (rand() % 2)
        zombies.push_back(new Zombie(3, 10, 100, "regular"));
}
void game::add_sun()
{
    Time interval_add_sun = seconds(5);
    add_sun_time += add_sun_clock.restart();
    if (add_sun_time >= interval_add_sun)
    {
        suns.push_back(new Sun(random() % 780 + 200));
        add_sun_time -= interval_add_sun;
    }
}

void game::add_pea(string type, int line, int start_x)
{
    peas.push_back(new Pea(type, line, start_x));
}
