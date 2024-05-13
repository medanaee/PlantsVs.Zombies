#include "Game.hpp"

bool Game::running()
{
    return window->isOpen();
}

void Game::add_pea(string type, int line, int start_x, int damage)
{
    peas.push_back(new Pea(type, line, start_x, damage));
}

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

Sprite Game::background()
{
    background_texture.loadFromFile("./Pics/Main Items/Background.png");
    Sprite background_sprite;
    background_sprite.setTexture(background_texture);
    return background_sprite;
}

Game::Game()
    : frozen_shooter_packet("FrozenPeaShooter", 120, "./Pics/Main Items/Seed-Packet/Frozen Pea-Shooter.png", "./Pics/Main Items/Seed-Packet/Frozen Pea-Shooter Dark.png", "./Pics/Frozen Pea-Shooter Plant/Idle/Idle01.png", Vector2f(13, 243), seconds(1)),
      wall_nut_packet("WallNut", 75, "./Pics/Main Items/Seed-Packet/Wall-Nut.png", "./Pics/Main Items/Seed-Packet/Wall-Nut Dark.png", "./Pics/Wall-Nut Plant/Full.png", Vector2f(13, 310), seconds(1)),
      shooter_packet("PeaShooter", 100, "./Pics/Main Items/Seed-Packet/Pea-Shooter.png", "./Pics/Main Items/Seed-Packet/Pea-Shooter Dark.png", "./Pics/Pea-Shooter Plant/Idle/Idle01.png", Vector2f(13, 176), seconds(1)),
      sun_flower_packet("SunFlower", 50, "./Pics/Main Items/Seed-Packet/SunFlower.png", "./Pics/Main Items/Seed-Packet/SunFlower Dark.png", "./Pics/SunFlower Plant/Idle01.png", Vector2f(13, 109), seconds(1)),
      melon_packet("Melon", 300, "./Pics/Main Items/Seed-Packet/Melon.png", "./Pics/Main Items/Seed-Packet/Melon Dark.png", "", Vector2f(13, 377), seconds(1)),
      sun_packet(5100, "./Pics/Main Items/Sun Bar.png", Vector2f(0, 12))
{
    window = new RenderWindow(VideoMode(1080, 720), "Plants VS. Zombies", Style::Close);
    for (int i = 0; i < 5; i++)
        table.push_back(new Row(Vector2f(223, 145 + i * 108), i + 1));
}

void Game::render_frozen_shooter_packet()
{
    window->draw(frozen_shooter_packet.get_sprite());
    window->draw(frozen_shooter_packet.get_remaining_time());
    window->draw(frozen_shooter_packet.plant_price());
}
void Game::render_wall_nut_packet()
{
    window->draw(wall_nut_packet.get_sprite());
    window->draw(wall_nut_packet.get_remaining_time());
    window->draw(wall_nut_packet.plant_price());
}
void Game::render_shooter_packet()
{
    window->draw(shooter_packet.get_sprite());
    window->draw(shooter_packet.get_remaining_time());
    window->draw(shooter_packet.plant_price());
}
void Game::render_sun_flower_packet()
{
    window->draw(sun_flower_packet.get_sprite());
    window->draw(sun_flower_packet.get_remaining_time());
    window->draw(sun_flower_packet.plant_price());
}
void Game::render_melon_packet()
{
    window->draw(melon_packet.get_sprite());
    window->draw(melon_packet.get_remaining_time());
    window->draw(melon_packet.plant_price());
}
void Game::render_sun_packet()
{
    window->draw(sun_packet.get_sprite());
    window->draw(sun_packet.write_budget());
}

void Game::render_packets()
{
    render_melon_packet();
    render_frozen_shooter_packet();
    render_shooter_packet();
    render_wall_nut_packet();
    render_sun_flower_packet();
    render_sun_packet();
}

void Game::update_packets()
{
    melon_packet.update(sun_packet.get_budget());
    wall_nut_packet.update(sun_packet.get_budget());
    shooter_packet.update(sun_packet.get_budget());
    frozen_shooter_packet.update(sun_packet.get_budget());
    sun_flower_packet.update(sun_packet.get_budget());
}

void Game::render_table()
{
    for (Row *&temp : table)
        for (int i = 0; i < 9; i++)
            window->draw(temp->get_block(i)->get_area());
}

void Game::render_peas()
{
    for (Pea *temp : peas)
        window->draw(temp->get_sprite());
}

void Game::render_line_zombies(int line)
{
    for (Zombie *temp : zombies)
        if (temp->get_line() == line)
            window->draw(temp->get_sprite());
}
void Game::render_zombies()
{
    for (int i = 1; i <= 5; i++)
        render_line_zombies(i);
}

void Game::render_suns()
{
    for (Sun *temp : suns)
        window->draw(temp->get_sprite());
}

void Game::update_zombies()
{
    for (Zombie *temp : zombies)
    {
        temp->update();
        if (temp->get_status() == "DIE")
        {
            delete temp;
            zombies.erase(find(zombies.begin(), zombies.end(), temp));
        }
    }
}

void Game::update_peas()
{
    for (Pea *temp : peas)
    {
        temp->update();
        if (temp->get_sprite().getPosition().x >= window->getSize().x)
        {
            delete temp;
            peas.erase(find(peas.begin(), peas.end(), temp));
        }
    }
}

void Game::check_collision()
{
    for (Zombie *temp_zombie : zombies)
    {
        for (Pea *temp_pea : peas)
        {
            if (is_colliding(temp_zombie->get_sprite(), temp_pea->get_sprite()) && temp_pea->get_line() == temp_zombie->get_line())
            {
                temp_zombie->getting_hit(*temp_pea);
                delete temp_pea;
                peas.erase(find(peas.begin(), peas.end(), temp_pea));
            }
        }
    }
}

void Game::check_mouse_click()
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
                        update_packets();
                    }
                ////////////////////////////////////////////////////////////////////////////////
                if (shooter_packet.get_sprite().getGlobalBounds().contains(mousePosition.x, mousePosition.y) && shooter_packet.is_avaliable())
                {
                    shooter_packet.select();
                    shooter_packet.set_plant_pos((Vector2f)mousePosition);
                }
                if (shooter_packet.get_select())
                {
                    for (Row *&temp : table)
                        for (int i = 0; i < 9; i++)
                            if (temp->get_block(i)->get_area().getGlobalBounds().contains(mousePosition.x, mousePosition.y) && temp->get_block(i)->get_plant() == nullptr)
                            {
                                add_plant("PeaShooter", 20, temp->get_block(i));
                                shooter_packet.release();
                                shooter_packet.reset_remaining_time();
                                sun_packet.spend_money(shooter_packet.get_price());
                                temp->get_block(i)->reset_area_color();
                            }
                }
                ///////////////////////////////////////////////////////////////////////////////

                if (frozen_shooter_packet.get_sprite().getGlobalBounds().contains(mousePosition.x, mousePosition.y) && frozen_shooter_packet.is_avaliable())
                {
                    frozen_shooter_packet.select();
                    frozen_shooter_packet.set_plant_pos((Vector2f)mousePosition);
                }

                if (frozen_shooter_packet.get_select())
                {
                    for (Row *&temp : table)
                        for (int i = 0; i < 9; i++)
                            if (temp->get_block(i)->get_area().getGlobalBounds().contains(mousePosition.x, mousePosition.y) && temp->get_block(i)->get_plant() == nullptr)
                            {
                                add_plant("FrozenPeaShooter", 20, temp->get_block(i));
                                frozen_shooter_packet.release();
                                frozen_shooter_packet.reset_remaining_time();
                                sun_packet.spend_money(frozen_shooter_packet.get_price());
                                temp->get_block(i)->reset_area_color();
                            }
                }

                ///////////////////////////////////////////////////////////////////////////////

                if (sun_flower_packet.get_sprite().getGlobalBounds().contains(mousePosition.x, mousePosition.y) && sun_flower_packet.is_avaliable())
                {
                    sun_flower_packet.select();
                    sun_flower_packet.set_plant_pos((Vector2f)mousePosition);
                }

                if (sun_flower_packet.get_select())
                {
                    for (Row *&temp : table)
                        for (int i = 0; i < 9; i++)
                            if (temp->get_block(i)->get_area().getGlobalBounds().contains(mousePosition.x, mousePosition.y) && temp->get_block(i)->get_plant() == nullptr)
                            {
                                add_plant("SunFlower", 20, temp->get_block(i));
                                sun_flower_packet.release();
                                sun_flower_packet.reset_remaining_time();
                                sun_packet.spend_money(sun_flower_packet.get_price());
                                temp->get_block(i)->reset_area_color();
                            }
                }

                ///////////////////////////////////////////////////////////////////////////////

                if (wall_nut_packet.get_sprite().getGlobalBounds().contains(mousePosition.x, mousePosition.y) && wall_nut_packet.is_avaliable())
                {
                    wall_nut_packet.select();
                    wall_nut_packet.set_plant_pos((Vector2f)mousePosition);
                }

                if (wall_nut_packet.get_select())
                {
                    for (Row *&temp : table)
                        for (int i = 0; i < 9; i++)
                            if (temp->get_block(i)->get_area().getGlobalBounds().contains(mousePosition.x, mousePosition.y) && temp->get_block(i)->get_plant() == nullptr)
                            {
                                add_plant("WallNut", 400, temp->get_block(i));
                                wall_nut_packet.release();
                                wall_nut_packet.reset_remaining_time();
                                sun_packet.spend_money(wall_nut_packet.get_price());
                                temp->get_block(i)->reset_area_color();
                            }
                }
            }
        }
        if (event.type == Event::MouseMoved)
        {
            Vector2i mousePosition = Mouse::getPosition(*window);
            if (shooter_packet.get_select() || frozen_shooter_packet.get_select() || sun_flower_packet.get_select() || wall_nut_packet.get_select())
            {
                shooter_packet.set_plant_pos((Vector2f)mousePosition);
                frozen_shooter_packet.set_plant_pos((Vector2f)mousePosition);
                sun_flower_packet.set_plant_pos((Vector2f)mousePosition);
                wall_nut_packet.set_plant_pos((Vector2f)mousePosition);
                for (Row *&temp : table)
                    for (int i = 0; i < 9; i++)
                        if (temp->get_block(i)->get_area().getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                            temp->get_block(i)->highlight_area();
                        else
                            temp->get_block(i)->reset_area_color();
            }
        }
    }
}

bool Game::have_zombie_in_front(Plant *plant)
{
    for (Zombie *temp : zombies)
        if (temp->get_line() == plant->get_block()->get_line() && temp->get_sprite().getPosition().x + 69 > plant->get_block()->get_position().x)
            return 1;
    return 0;
}

void Game::update_suns()
{
    for (Sun *&temp : suns)
    {
        temp->update();
        if (temp->get_position().y > window->getSize().y || temp->is_die())
        {
            delete temp;
            suns.erase(find(suns.begin(), suns.end(), temp));
        }
    }
}

void Game::add_sun_from_top()
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

void Game::render()
{
    window->clear();

    window->draw(background());
    render_peas();
    for (Plant *temp : plants)
    {
        window->draw(temp->get_sprite());
    }

    render_table();

    render_zombies();
    // render_plants();
    render_packets();
    render_suns();

    if (shooter_packet.get_select())
    {
        window->draw(shooter_packet.get_plant_sprite());
    }
    if (frozen_shooter_packet.get_select())
    {
        window->draw(frozen_shooter_packet.get_plant_sprite());
    }
    if (sun_flower_packet.get_select())
    {
        window->draw(sun_flower_packet.get_plant_sprite());
    }
    if (wall_nut_packet.get_select())
    {
        window->draw(wall_nut_packet.get_plant_sprite());
    }

    window->display();
}

/////////////////////////////////////////////////////////////////
void Game::update()
{

    for (Plant *temp : plants)
    {
        temp->update(have_zombie_in_front(temp), this);
        if (temp->get_health() <= 0)
        {
            temp->get_block()->set_plant(nullptr);
            delete temp;
            plants.erase(find(plants.begin(), plants.end(), temp));
        }
    }

    update_packets();
    check_mouse_click();
    add_sun_from_top();
    // add_zombie();
    // add_peas_test();

    update_zombies();
    update_suns();
    update_peas();

    check_collision();

    for (Zombie *temp_zombie : zombies)
    {
        Block *zombie_block = nullptr;
        for (Row *&temp_row : table)
            for (int i = 0; i < 9; i++)
            {
                Block *temp_block = temp_row->get_block(i);
                if (temp_zombie->get_line() == temp_block->get_line() && temp_zombie->get_sprite().getPosition().x + 69 <= temp_block->get_position().x + temp_block->get_area().getSize().x && temp_zombie->get_sprite().getPosition().x + 69 >= temp_block->get_position().x)
                {
                    zombie_block = temp_block;
                    break;
                }
                if (zombie_block != nullptr)
                    break;
            }
        if (zombie_block != nullptr)
        {
            if (zombie_block->get_plant() != nullptr)
            {
                zombie_block->get_plant()->getting_hit(temp_zombie);
                temp_zombie->change_eating();
            }
            else
            {
                temp_zombie->change_no_eating();
            }
        }
    }
}
////////////////////////////////////////////////////////////////

void Game::add_zombie()
{
    Time interval_add_zombie = seconds(3);
    add_zombie_time += add_zombie_clock.restart();
    if (add_zombie_time >= interval_add_zombie)
    {
        if (rand() % 2)
            zombies.push_back(new Zombie(random() % 5 + 1, 10, 48, 10, "regular"));
        else
            zombies.push_back(new Zombie(rand() % 5 + 1, 10, 100, 15, "angry"));

        add_zombie_time -= interval_add_zombie;
    }
}

void Game::add_1zombie()
{
    zombies.push_back(new Zombie(3, 10, 34, 10, "regular"));
    zombies.push_back(new Zombie(3, 10, 34, 10, "regular"));
}

void Game::add_sun(Vector2f position)
{
    suns.push_back(new Sun(position));
}

void Game::add_peas_test()
{
    Time interval_add_pea = seconds(0.5f);
    add_peas_time += add_peas_clock.restart();
    if (add_peas_time >= interval_add_pea)
    {
        for (int i = 1; i <= 5; i++)
            add_pea("REGULAR", i, 10, 5);
        add_peas_time -= interval_add_pea;
    }
}

void Game::add_plant(string type, int health, Block *block)
{
    if (type == "WallNut")
    {
        plants.push_back(new Defender_Plant(health, block));
    }
    if (type == "SunFlower")
    {
        plants.push_back(new Sun_Plant(health, block));
    }
    if (type == "PeaShooter")
    {
        plants.push_back(new Invasive_Plant(health, block, "PeaShooter"));
    }
    if (type == "FrozenPeaShooter")
    {
        plants.push_back(new Invasive_Plant(health, block, "FrozenPeaShooter"));
    }
    if (type == "Melon")
    {
    }
}

vector<Row *> Game::get_table()
{
    return table;
}
