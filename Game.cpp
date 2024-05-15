#include "Game.hpp"

bool Game::running() { return window->isOpen(); }
vector<Row *> Game::get_table() { return table; }
Sound *Game::get_shoot_pea_sound() { return &shoot_pea_sound; }
void Game::add_pea(string type, int line, int start_x, int damage, int speed) { peas.push_back(new Pea(type, line, start_x, damage, speed)); }

bool is_colliding(const Sprite &sprite1, const Sprite &sprite2)
{
    sf::FloatRect bounds1 = sprite1.getGlobalBounds();
    sf::FloatRect bounds2 = sprite2.getGlobalBounds();
    sf::FloatRect intersection;

    if (bounds1.intersects(bounds2, intersection))
    {
        int last_col = intersection.left + intersection.width;
        int start_y = intersection.top + intersection.height / 2;
        if (sprite1.getTexture()->copyToImage().getPixel(COLORED_PIXEL_POSITION).a > 0)
            return true;
    }
    return false;
}

Game::Game(Setting setting)
    : sun_packet(setting.sun_data.money, SUN_BAR_IMAGE, SUN_BAR_POSITION),
      sun_flower_packet(SUNFLOWER, setting.plants_data[0].price, LIGHT_SUNFLOWER_SEED_PCKET_IMAGE, DARK_SUNFLOWER_SEED_PCKET_IMAGE, "./Pics/SunFlower Plant/Idle01.png", SUNFLOWER_SEED_PCKET_POSITION, seconds(setting.time_data.recharge_duration)),
      shooter_packet(PEASHOOTER, setting.plants_data[1].price, LIGHT_PEASHOOTER_SEED_PCKET_IMAGE, DARK_PEASHOOTER_SEED_PCKET_IMAGE, "./Pics/PeaShooter Plant/Idle/Idle01.png", PEASHOOTER_SEED_PCKET_POSITION, seconds(setting.time_data.recharge_duration)),
      frozen_shooter_packet(FROZEN_PEASHOOTER, setting.plants_data[2].price, LIGHT_FROZEN_PEASHOOTER_SEED_PCKET_IMAGE,DARK_FROZEN_PEASHOOTER_SEED_PCKET_IMAGE, "./Pics/Frozen PeaShooter Plant/Idle/Idle01.png", FROZEN_PEASHOOTER_SEED_PCKET_POSITION, seconds(setting.time_data.recharge_duration)),
      wall_nut_packet(WALLNUT, setting.plants_data[3].price, LIGHT_WALLNUT_SEED_PCKET_IMAGE, DARK_WALLNUT_SEED_PCKET_IMAGE, "./Pics/WallNut Plant/Full.png", WALLNUT_SEED_PCKET_POSITION, seconds(setting.time_data.recharge_duration)),
      melon_packet(MELON, setting.plants_data[4].price, LIGHT_MELON_SEED_PCKET_IMAGE, DARK_MELON_SEED_PCKET_IMAGE, "./Pics/SunFlower Plant/Idle01.png", MELON_SEED_PCKET_POSITION, seconds(setting.time_data.recharge_duration))
{
    window = new RenderWindow(VideoMode(1080, 720), "Plants VS. Zombies", Style::Close);

    this->setting = setting;
    for (int i = 0; i < 5; i++)
        table.push_back(new Row(Vector2f(223, 145 + i * 108), i + 1));

    background_texture.loadFromFile(BACKGROUND);
    background.setTexture(background_texture);

    start_button_texture.loadFromFile(START_BOTTON);
    hover_start_button_texture.loadFromFile(HOVER_START_BOTTON);
    menu_texture.loadFromFile(MENU_IMAGE);

    menu.setTexture(menu_texture);
    start_button.setTexture(start_button_texture);
    start_button.setPosition(261, 178);

    lose_texture.loadFromFile(LOSE_PAGE);
    win_texture.loadFromFile(WIN_PAGE);

    main_buffer.loadFromFile(BACKGROUND_SOUND);
    main_sound.setBuffer(main_buffer);

    lose_buffer.loadFromFile(LOSE_SOUND);
    lose_sound.setBuffer(lose_buffer);

    win_buffer.loadFromFile(WIN_SOUND);
    win_sound.setBuffer(win_buffer);

    planting_plant_buffer.loadFromFile(PLANTING_SOUND);
    planting_plant_sound.setBuffer(planting_plant_buffer);

    eat_plant_buffer.loadFromFile(EAT_SOUND);
    eat_plant_sound.setBuffer(eat_plant_buffer);

    die_zombie_buffer.loadFromFile(DIE_SOUND);
    die_zombie_sound.setBuffer(die_zombie_buffer);

    shoot_pea_buffer.loadFromFile(SHOOT_SOUND);
    shoot_pea_sound.setBuffer(shoot_pea_buffer);
}

void Game::render_packets()
{
    melon_packet.show(window);
    frozen_shooter_packet.show(window);
    shooter_packet.show(window);
    wall_nut_packet.show(window);
    sun_flower_packet.show(window);
    sun_packet.show(window);
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
    for (Zombie *temp_zombie : zombies)
    {
        temp_zombie->update();

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
                zombie_block->get_plant()->eaten_by(temp_zombie);
                temp_zombie->change_eating(true);
                if (eat_plant_sound.getStatus() == SoundSource::Stopped)
                {
                    eat_plant_sound.play();
                }
            }
            else
            {
                temp_zombie->change_eating(false);
            }
        }

        if (temp_zombie->get_status() == IDLE)
        {
            page = "lose";
            main_sound.stop();
            lose_sound.play();
        }
    }

    for (auto it = zombies.begin(); it != zombies.end();)
    {
        Zombie *temp_zombie = *it;

        if (temp_zombie->get_play_die_sound())
            die_zombie_sound.play();
        if (temp_zombie->get_status() == DIE)
        {
            it = zombies.erase(it);
            delete temp_zombie;
        }
        else
            ++it;
    }
}

void Game::update_peas()
{
    for (auto it = peas.begin(); it != peas.end();)
    {
        Pea *temp_pea = *it;
        temp_pea->update();
        if (temp_pea->get_sprite().getPosition().x >= window->getSize().x)
        {
            it = peas.erase(it);
            delete temp_pea;
        }
        else
            ++it;
    }
}

void Game::check_collision()
{
    for (Zombie *temp_zombie : zombies)
    {
        for (auto it = peas.begin(); it != peas.end();)
        {
            Pea *temp_pea = *it;
            if (is_colliding(temp_zombie->get_sprite(), temp_pea->get_sprite()) && temp_pea->get_line() == temp_zombie->get_line())
            {
                temp_zombie->getting_hit(*temp_pea);
                it = peas.erase(it);
                delete temp_pea;
            }
            else
                ++it;
        }
    }
}

void Game::check_mouse_click()
{
    while (window->pollEvent(event))
    {
        if (event.type == Event::Closed)
            window->close();

        if (page == "gameplay")
        {

            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    Vector2i mouse_position = Mouse::getPosition(*window);

                    for (auto it = suns.begin(); it != suns.end();)
                    {
                        Sun *temp_sun = *it;
                        if (temp_sun->get_sprite().getGlobalBounds().contains(mouse_position.x, mouse_position.y))
                        {
                            sun_packet.add_money(50);
                            it = suns.erase(it);
                            delete temp_sun;
                        }
                        else
                            ++it;
                    }

                    if (shooter_packet.get_sprite().getGlobalBounds().contains(mouse_position.x, mouse_position.y) && shooter_packet.is_avaliable())
                    {
                        shooter_packet.select();
                        shooter_packet.show_preview((Vector2f)mouse_position);
                    }
                    if (shooter_packet.selection_status())
                    {
                        for (Row *&temp : table)
                            for (int i = 0; i < 9; i++)
                                if (temp->get_block(i)->get_area().getGlobalBounds().contains(mouse_position.x, mouse_position.y) && temp->get_block(i)->get_plant() == nullptr)
                                {
                                    planting_plant_sound.play();
                                    add_plant(PEASHOOTER, 20, temp->get_block(i));
                                    shooter_packet.release();
                                    shooter_packet.reset_remaining_time();
                                    sun_packet.spend_money(shooter_packet.cost());
                                    temp->get_block(i)->defaultlight_area();
                                }
                    }

                    if (frozen_shooter_packet.get_sprite().getGlobalBounds().contains(mouse_position.x, mouse_position.y) && frozen_shooter_packet.is_avaliable())
                    {
                        frozen_shooter_packet.select();
                        frozen_shooter_packet.show_preview((Vector2f)mouse_position);
                    }
                    if (frozen_shooter_packet.selection_status())
                    {
                        for (Row *&temp : table)
                            for (int i = 0; i < 9; i++)
                                if (temp->get_block(i)->get_area().getGlobalBounds().contains(mouse_position.x, mouse_position.y) && temp->get_block(i)->get_plant() == nullptr)
                                {
                                    planting_plant_sound.play();
                                    add_plant(FROZEN_PEASHOOTER, 20, temp->get_block(i));
                                    frozen_shooter_packet.release();
                                    frozen_shooter_packet.reset_remaining_time();
                                    sun_packet.spend_money(frozen_shooter_packet.cost());
                                    temp->get_block(i)->defaultlight_area();
                                }
                    }

                    if (sun_flower_packet.get_sprite().getGlobalBounds().contains(mouse_position.x, mouse_position.y) && sun_flower_packet.is_avaliable())
                    {
                        sun_flower_packet.select();
                        sun_flower_packet.show_preview((Vector2f)mouse_position);
                    }
                    if (sun_flower_packet.selection_status())
                    {
                        for (Row *&temp : table)
                            for (int i = 0; i < 9; i++)
                                if (temp->get_block(i)->get_area().getGlobalBounds().contains(mouse_position.x, mouse_position.y) && temp->get_block(i)->get_plant() == nullptr)
                                {
                                    planting_plant_sound.play();
                                    add_plant(SUNFLOWER, 20, temp->get_block(i));
                                    sun_flower_packet.release();
                                    sun_flower_packet.reset_remaining_time();
                                    sun_packet.spend_money(sun_flower_packet.cost());
                                    temp->get_block(i)->defaultlight_area();
                                }
                    }

                    if (wall_nut_packet.get_sprite().getGlobalBounds().contains(mouse_position.x, mouse_position.y) && wall_nut_packet.is_avaliable())
                    {
                        wall_nut_packet.select();
                        wall_nut_packet.show_preview((Vector2f)mouse_position);
                    }
                    if (wall_nut_packet.selection_status())
                    {
                        for (Row *&temp : table)
                            for (int i = 0; i < 9; i++)
                                if (temp->get_block(i)->get_area().getGlobalBounds().contains(mouse_position.x, mouse_position.y) && temp->get_block(i)->get_plant() == nullptr)
                                {
                                    planting_plant_sound.play();
                                    add_plant(WALLNUT, 400, temp->get_block(i));
                                    wall_nut_packet.release();
                                    wall_nut_packet.reset_remaining_time();
                                    sun_packet.spend_money(wall_nut_packet.cost());
                                    temp->get_block(i)->defaultlight_area();
                                }
                    }
                }
            }

            else if (event.type == Event::MouseMoved)
            {
                Vector2i mouse_position = Mouse::getPosition(*window);
                if (shooter_packet.selection_status() || frozen_shooter_packet.selection_status() || sun_flower_packet.selection_status() || wall_nut_packet.selection_status())
                {
                    shooter_packet.show_preview((Vector2f)mouse_position);
                    frozen_shooter_packet.show_preview((Vector2f)mouse_position);
                    sun_flower_packet.show_preview((Vector2f)mouse_position);
                    wall_nut_packet.show_preview((Vector2f)mouse_position);

                    for (Row *&temp : table)
                        for (int i = 0; i < 9; i++)
                            if (temp->get_block(i)->get_area().getGlobalBounds().contains(mouse_position.x, mouse_position.y))
                                temp->get_block(i)->highlight_area();
                            else
                                temp->get_block(i)->defaultlight_area();
                }
            }
        }

        if (page == MENU)
        {
            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    Vector2i mouse_position = Mouse::getPosition(*window);
                    if (start_button.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
                    {
                        global_clock.restart();
                        page = "gameplay";
                    }
                }
            }
            else if (event.type == Event::MouseMoved)
            {
                Vector2i mouse_position = Mouse::getPosition(*window);
                if (start_button.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
                    start_button.setTexture(hover_start_button_texture);
                else
                    start_button.setTexture(start_button_texture);
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
    for (auto it = suns.begin(); it != suns.end();)
    {
        Sun *temp_sun = *it;
        temp_sun->update();
        if (temp_sun->get_position().y > window->getSize().y || temp_sun->is_die())
        {
            it = suns.erase(it);
            delete temp_sun;
        }
        else
            ++it;
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

void Game::add_zombie()
{

    add_zombie_time += add_zombie_clock.restart();
    if (add_zombie_time >= interval_add_zombie)
    {
        if (rand() % 2)
        {
            zombies.push_back(new Zombie(random() % 5 + 1, 10, 48, 10, REGULAR));
        }
        else
        {
            zombies.push_back(new Zombie(random() % 5 + 1, 10, 100, 15, ANGRY));
        }
        add_zombie_time -= interval_add_zombie;
    }
}

void Game::add_sun(Vector2f position)
{
    suns.push_back(new Sun(position));
}

void Game::add_plant(string type, int health, Block *block)
{
    if (type == WALLNUT)
    {
        plants.push_back(new Defender_Plant(health, block));
    }
    if (type == SUNFLOWER)
    {
        plants.push_back(new Sun_Plant(health, block, 8));
    }
    if (type == PEASHOOTER)
    {
        plants.push_back(new Invasive_Plant(health, block, PEASHOOTER, seconds(3)));
    }
    if (type == FROZEN_PEASHOOTER)
    {
        plants.push_back(new Invasive_Plant(health, block, FROZEN_PEASHOOTER, seconds(3)));
    }
    if (type == MELON)
    {
    }
}

// render:

void Game::render()
{
    window->clear();

    if (page == MENU)
    {
        window->draw(menu);
        window->draw(start_button);
    }
    if (page == "gameplay")
    {
        window->draw(background);
        render_peas();
        for (Plant *temp : plants)
        {
            window->draw(temp->get_sprite());
        }

        render_table();

        render_zombies();
        render_packets();
        render_suns();

        if (shooter_packet.selection_status())
        {
            window->draw(shooter_packet.get_plant_sprite());
        }
        if (frozen_shooter_packet.selection_status())
        {
            window->draw(frozen_shooter_packet.get_plant_sprite());
        }
        if (sun_flower_packet.selection_status())
        {
            window->draw(sun_flower_packet.get_plant_sprite());
        }
        if (wall_nut_packet.selection_status())
        {
            window->draw(wall_nut_packet.get_plant_sprite());
        }
    }
    if (page == "lose" || page == "win")
    {
        window->draw(background);
    }

    window->display();
}

// update:

void Game::update()
{
    check_mouse_click();
    if (page == MENU)
    {
        if (main_sound.getStatus() == SoundSource::Stopped)
        {
            main_sound.play();
        }
    }
    if (page == "gameplay")
    {
        change_zombie_rate();
        add_zombie();
        // add_peas_test();

        for (auto it = plants.begin(); it != plants.end();)
        {
            Plant *temp_plant = *it;
            temp_plant->update(have_zombie_in_front(temp_plant), this);
            if (temp_plant->get_health() <= 0)
            {
                temp_plant->get_block()->put_plant(nullptr);
                it = plants.erase(it);
                delete temp_plant;
            }
            else
                ++it;
        }
        update_packets();
        add_sun_from_top();

        update_zombies();
        update_suns();
        update_peas();

        check_collision();

        global_time += global_clock.restart();

        if (global_time >= seconds(100))
        {
            page = "win";
            main_sound.stop();
            win_sound.play();
        }
    }
    if (page == "lose")
    {
        background.setTexture(lose_texture);
    }
    if (page == "win")
    {
        background.setTexture(win_texture);
    }

    // cout << interval_add_zombie.asSeconds() << endl;
}

////////////////////////////////////////////////////////////////

// test functions:

void Game::add_1zombie()
{
    zombies.push_back(new Zombie(3, 10, 34, 10, REGULAR));
    zombies.push_back(new Zombie(3, 10, 34, 10, REGULAR));
}

void Game::change_zombie_rate()
{
    Time interval_zombie_rate = seconds(8);
    zombie_rate_time += zombie_rate_clock.restart();
    if (zombie_rate_time >= interval_zombie_rate)
    {
        interval_add_zombie = seconds(interval_add_zombie.asSeconds() - 1);
        zombie_rate_time -= interval_zombie_rate;
    }
}

void Game::add_peas_test()
{
    Time interval_add_pea = seconds(3.0f);
    add_peas_time += add_peas_clock.restart();
    if (add_peas_time >= interval_add_pea)
    {
        for (int i = 1; i <= 5; i++)
            add_pea(REGULAR, i, 10, 5, 2);
        add_peas_time -= interval_add_pea;
    }
}