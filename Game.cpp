#include "Game.hpp"

bool game::running() { return window->isOpen(); }
void game::add_pea(string type, int line, int start_x, int damage) { peas.push_back(new Pea(type, line, start_x, damage)); }

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

Sprite game::background()
{
    background_texture.loadFromFile("./Pics/Main Items/Background.png");
    Sprite background_sprite;
    background_sprite.setTexture(background_texture);
    return background_sprite;
}

game::game()
    : frozen_shooter_packet(120, "./Pics/Main Items/Seed-Packet/Frozen Pea-Shooter.png", "./Pics/Main Items/Seed-Packet/Frozen Pea-Shooter Dark.png", Vector2f(13, 243)),
      wall_nut_packet(75, "./Pics/Main Items/Seed-Packet/Wall-Nut.png", "./Pics/Main Items/Seed-Packet/Wall-Nut Dark.png", Vector2f(13, 310)),
      shooter_packet(100, "./Pics/Main Items/Seed-Packet/Pea-Shooter.png", "./Pics/Main Items/Seed-Packet/Pea-Shooter Dark.png", Vector2f(13, 176)),
      sun_flower_packet(50, "./Pics/Main Items/Seed-Packet/SunFlower.png", "./Pics/Main Items/Seed-Packet/SunFlower Dark.png", Vector2f(13, 109)),
      melon_packet(300, "./Pics/Main Items/Seed-Packet/Melon.png", "./Pics/Main Items/Seed-Packet/Melon Dark.png", Vector2f(13, 377)),
      sun_packet(budget, "./Pics/Main Items/Sun Bar.png", Vector2f(0, 12))
{
    window = new RenderWindow(VideoMode(1080, 720), "Plants VS. Zombies", Style::Close);
    for (int i = 0; i < 5; i++)
        table.push_back(new Row(Vector2f(223, 145 + i * 108)));
}

void game::render_frozen_shooter_packet()
{
    window->draw(frozen_shooter_packet.get_sprite());
    window->draw(frozen_shooter_packet.get_remaining_time());
    window->draw(frozen_shooter_packet.plant_price());
}
void game::render_wall_nut_packet()
{
    window->draw(wall_nut_packet.get_sprite());
    window->draw(wall_nut_packet.get_remaining_time());
    window->draw(wall_nut_packet.plant_price());
}
void game::render_shooter_packet()
{
    window->draw(shooter_packet.get_sprite());
    window->draw(shooter_packet.get_remaining_time());
    window->draw(shooter_packet.plant_price());
}
void game::render_sun_flower_packet()
{
    window->draw(sun_flower_packet.get_sprite());
    window->draw(sun_flower_packet.get_remaining_time());
    window->draw(sun_flower_packet.plant_price());
}
void game::render_melon_packet()
{
    window->draw(melon_packet.get_sprite());
    window->draw(melon_packet.get_remaining_time());
    window->draw(melon_packet.plant_price());
}
void game::render_sun_packet()
{
    window->draw(sun_packet.get_sprite());
    window->draw(sun_packet.write_budget());
}
void game::render_packets()
{
    render_melon_packet();
    render_frozen_shooter_packet();
    render_shooter_packet();
    render_wall_nut_packet();
    render_sun_flower_packet();
    render_sun_packet();
}

void game::update_packets()
{
    melon_packet.update_image(budget);
    wall_nut_packet.update_image(budget);
    shooter_packet.update_image(budget);
    frozen_shooter_packet.update_image(budget);
    sun_flower_packet.update_image(budget);
}

// void game::render_plants()
// {
//     render_line_plants(1);
//     render_line_plants(2);
//     render_line_plants(3);
//     render_line_plants(4);
//     render_line_plants(5);
// }

void game::render_table()
{
    for (Row *&temp : table)
        for (int i = 0; i < 9; i++)
            window->draw(temp->get_block(i)->get_area());
}

void game::render_peas()
{
    for (Pea *temp : peas)
        window->draw(temp->get_sprite());
}

void game::render_line_zombies(int line)
{
    for (Zombie *temp : zombies)
        if (temp->get_line() == line)
            window->draw(temp->get_sprite());
}
void game::render_zombies()
{
    render_line_zombies(1);
    render_line_zombies(2);
    render_line_zombies(3);
    render_line_zombies(4);
    render_line_zombies(5);
}

void game::render_suns()
{
    for (Sun *temp : suns)
        window->draw(temp->get_sprite());
}

void game::update_zombies()
{
    for (Zombie *temp : zombies)
        temp->update();
}

void game::update_peas()
{
    for (Pea *temp : peas)
        temp->update();
}

void game::check_collision()
{
    for (Zombie *temp_zombie : zombies)
    {
        for (Pea *temp_pea : peas)
        {
            if (is_colliding(temp_zombie->get_sprite(), temp_pea->get_sprite()) && temp_pea->get_line() == temp_zombie->get_line())
            {
                temp_zombie->getting_hit(*temp_pea);
                if (temp_zombie->get_health() <= 0)
                {
                    delete temp_zombie;
                    zombies.erase(find(zombies.begin(), zombies.end(), temp_zombie));
                }
                delete temp_pea;
                peas.erase(find(peas.begin(), peas.end(), temp_pea));
            }
        }
    }
}

void game::check_mouse_click()
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
                        // 25 hamon sun_value hast
                        sun_packet.add_money(25);
                        budget += 25;
                        update_packets();
                    }
            }
        }
        else if (event.type == Event::MouseMoved)
        {
            Vector2i mousePosition = Mouse::getPosition(*window);
            for (Row *&temp : table)
                for (int i = 0; i < 9; i++)
                    if (temp->get_block(i)->get_area().getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                        temp->get_block(i)->highlight_area();
                    else
                        temp->get_block(i)->reset_area_color();
        }
    }
}

void game::update_suns()
{
    for (Sun *&temp : suns)
    {
        temp->update();
        if (temp->get_position().y > window->getSize().y)
        {
            delete temp;
            suns.erase(find(suns.begin(), suns.end(), temp));
        }
    }
}

void game::add_sun()
{
    Time interval_add_sun = seconds(5);
    add_sun_time += add_sun_clock.restart();
    if (add_sun_time >= interval_add_sun)
    {
        suns.push_back(new Sun(random() % 780 + 200, 3));
        add_sun_time -= interval_add_sun;
    }
}

//////////////////////////////////////////////////////////////////

void game::render()
{
    window->clear();

    window->draw(background());

    render_table();
    render_peas();
    render_zombies();
    // render_plants();
    render_packets();
    render_suns();

    window->display();
}

/////////////////////////////////////////////////////////////////
void game::update()
{

    update_packets();
    check_mouse_click();
    add_sun();
    // add_zombie();

    // update_plants();
    update_zombies();
    update_suns();
    update_peas();

    check_collision();
}
////////////////////////////////////////////////////////////////

void game::add_zombie()
{
    Time interval_add_zombie = seconds(1);
    add_zombie_time += add_zombie_clock.restart();
    if (add_zombie_time >= interval_add_zombie)
    {
        if (rand() % 2)
            zombies.push_back(new Zombie(random() % 5 + 1, 10, 12, "regular"));
        else
            zombies.push_back(new Zombie(rand() % 5 + 1, 10, 34, "angry"));

        add_zombie_time -= interval_add_zombie;
    }
}

void game::add_1zombie()
{
    zombies.push_back(new Zombie(random() % 5 + 1, 10, 12, "regular"));
}
