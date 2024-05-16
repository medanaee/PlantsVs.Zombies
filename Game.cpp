#include "Game.hpp"

bool Game::running() { return window->isOpen(); }

vector<Row *> Game::get_table() { return table; }

Sound *Game::get_shoot_pea_sound() { return &shoot_pea_sound; }

Setting *Game::get_setting() { return &setting; }

void Game::add_pea(string type, int line, int start_x, int damage, int speed) { peas.push_back(new Pea(type, line, start_x, damage, speed)); }

void Game::add_melon(Zombie *target, int line, int start_x, int damage, Time all_time) { melons.push_back(new Melon(target, line, start_x, damage, all_time)); }

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

Zombie *Game::find_target_zombie(Plant *plant)
{
    vector<Zombie *> same_line_zombies;
    Zombie *target = nullptr;
    for (Zombie *temp_zombie : zombies)
        if (plant->get_block()->get_line() == temp_zombie->get_line() && temp_zombie->get_sprite().getPosition().x + ZOMBIE_DISTANSE_FROM_SPRITE >= plant->get_block()->get_position().x)
            same_line_zombies.push_back(temp_zombie);

    if (same_line_zombies.size() != 0)
        target = same_line_zombies[0];

    for (Zombie *temp_zombie : same_line_zombies)
        if (temp_zombie->get_sprite().getPosition().x < target->get_sprite().getPosition().x)
            target = temp_zombie;

    return target;
}

void Game::extract_sounds()
{
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

void Game::extract_menu_images()
{
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
}

Game::Game(Setting setting)
    : sun_packet(setting.sun_data.budget, SUN_BAR_IMAGE, SUN_BAR_POSITION),
      sun_flower_packet(SUNFLOWER, setting.plants_data[0].price, LIGHT_SUNFLOWER_SEED_PCKET_IMAGE, DARK_SUNFLOWER_SEED_PCKET_IMAGE, SUNFLOWER_PREVIEW, SUNFLOWER_SEED_PCKET_POSITION, seconds(setting.time_data.recharge_duration)),
      shooter_packet(PEASHOOTER, setting.plants_data[1].price, LIGHT_PEASHOOTER_SEED_PCKET_IMAGE, DARK_PEASHOOTER_SEED_PCKET_IMAGE, PEASHOOTER_PREVIEW, PEASHOOTER_SEED_PCKET_POSITION, seconds(setting.time_data.recharge_duration)),
      frozen_shooter_packet(FROZEN_PEASHOOTER, setting.plants_data[2].price, LIGHT_FROZEN_PEASHOOTER_SEED_PCKET_IMAGE, DARK_FROZEN_PEASHOOTER_SEED_PCKET_IMAGE, FROZEN_PEASHOOTER_PREVIEW, FROZEN_PEASHOOTER_SEED_PCKET_POSITION, seconds(setting.time_data.recharge_duration)),
      wall_nut_packet(WALLNUT, setting.plants_data[3].price, LIGHT_WALLNUT_SEED_PCKET_IMAGE, DARK_WALLNUT_SEED_PCKET_IMAGE, PERFECT_HEALTH_IMAGE, WALLNUT_SEED_PCKET_POSITION, seconds(setting.time_data.recharge_duration)),
      melon_packet(MELON, setting.plants_data[4].price, LIGHT_MELON_SEED_PCKET_IMAGE, DARK_MELON_SEED_PCKET_IMAGE, MELON_PREVIEW, MELON_SEED_PCKET_POSITION, seconds(setting.time_data.recharge_duration))
{
    window = new RenderWindow(WINDOW_CONSTRUCTOR);

    this->setting = setting;
    for (int i = 0; i < 5; i++)
        table.push_back(new Row(ROW_CONSTRUCTOR));

    extract_menu_images();
    extract_sounds();
}

void Game::is_die_zombies()
{
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

Block *Game::find_zombie_block(Zombie *temp_zombie)
{
    for (Row *&temp_row : table)
        for (int i = 0; i < 9; i++)
        {
            Block *temp_block = temp_row->get_block(i);
            if (temp_zombie->get_line() == temp_block->get_line() &&
                temp_zombie->get_sprite().getPosition().x + ZOMBIE_DISTANSE_FROM_SPRITE <= temp_block->get_position().x + temp_block->get_area().getSize().x &&
                temp_zombie->get_sprite().getPosition().x + ZOMBIE_DISTANSE_FROM_SPRITE >= temp_block->get_position().x)
                return temp_block;
        }
    return nullptr;
}

void Game::end()
{
    page = LOSE;
    main_sound.stop();
    lose_sound.play();
}

void Game::mouse_move()
{
    Vector2i mouse_position = Mouse::getPosition(*window);
    if (shooter_packet.selection_status() || frozen_shooter_packet.selection_status() || sun_flower_packet.selection_status() || wall_nut_packet.selection_status() || melon_packet.selection_status())
    {
        shooter_packet.show_preview((Vector2f)mouse_position);
        frozen_shooter_packet.show_preview((Vector2f)mouse_position);
        sun_flower_packet.show_preview((Vector2f)mouse_position);
        wall_nut_packet.show_preview((Vector2f)mouse_position);
        melon_packet.show_preview((Vector2f)mouse_position);

        for (Row *&temp : table)
            for (int i = 0; i < 9; i++)
                if (temp->get_block(i)->get_area().getGlobalBounds().contains(mouse_position.x, mouse_position.y))
                    temp->get_block(i)->highlight_area();
                else
                    temp->get_block(i)->defaultlight_area();
    }
}

void Game::update_zombies()
{
    for (Zombie *temp_zombie : zombies)
    {
        temp_zombie->update();
        Block *zombie_block = find_zombie_block(temp_zombie);
        if (zombie_block != nullptr)
            if (zombie_block->get_plant() != nullptr)
            {
                zombie_block->get_plant()->eaten_by(temp_zombie);
                temp_zombie->change_eating(true);
                if (eat_plant_sound.getStatus() == SoundSource::Stopped)
                    eat_plant_sound.play();
            }
            else
                temp_zombie->change_eating(false);

        if (temp_zombie->get_status() == IDLE)
            end();
    }
    is_die_zombies();
}

void Game::update_packets()
{
    melon_packet.update(sun_packet.get_budget());
    wall_nut_packet.update(sun_packet.get_budget());
    shooter_packet.update(sun_packet.get_budget());
    frozen_shooter_packet.update(sun_packet.get_budget());
    sun_flower_packet.update(sun_packet.get_budget());
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

void Game::update_melons()
{
    for (auto it = melons.begin(); it != melons.end();)
    {
        Melon *temp_melon = *it;
        temp_melon->update();
        if (temp_melon->get_target()->get_health() > 0 &&
                is_colliding(temp_melon->get_target()->get_sprite(), temp_melon->get_sprite()) &&
                temp_melon->get_line() == temp_melon->get_target()->get_line() ||
            temp_melon->get_sprite().getPosition().y + 60 > 144 + 108 * (temp_melon->get_line()))
        {
            temp_melon->get_target()->getting_hit(*temp_melon);
            it = melons.erase(it);
            delete temp_melon;
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
                temp_zombie->getting_hit(*temp_pea, setting.plants_data[2].cooldown);
                it = peas.erase(it);
                delete temp_pea;
            }
            else
                ++it;
        }
    }
}

bool Game::click_suns(Vector2f mouse_position)
{
    for (auto it = suns.begin(); it != suns.end();)
    {
        Sun *temp_sun = *it;
        if (temp_sun->get_sprite().getGlobalBounds().contains(mouse_position.x, mouse_position.y))
        {
            sun_packet.add_money(setting.sun_data.money);
            it = suns.erase(it);
            delete temp_sun;
            return 1;
        }
        else
            ++it;
    }
    return 0;
}


void Game::put_plant(Vector2f mouse_position, bool sun_collect, Seed_Packet &seed_packet)
{
    bool select_packet = 0;
    if (seed_packet.get_sprite().getGlobalBounds().contains(mouse_position.x, mouse_position.y) && seed_packet.is_avaliable())
    {
        select_packet = 1;
        seed_packet.select();
        seed_packet.show_preview(mouse_position);
    }
    if (seed_packet.selection_status() && !sun_collect)
    {
        bool select_any_block = 0;
        for (Row *&temp : table)
            for (int i = 0; i < 9; i++)
                if (temp->get_block(i)->get_area().getGlobalBounds().contains(mouse_position.x, mouse_position.y) && temp->get_block(i)->get_plant() == nullptr)
                {
                    select_any_block = 1;
                    planting_plant_sound.play();
                    if (&seed_packet == &sun_flower_packet)
                        add_plant(SUNFLOWER, setting.plants_data[0].health, temp->get_block(i));
                    if (&seed_packet == &shooter_packet)
                        add_plant(PEASHOOTER, setting.plants_data[1].health, temp->get_block(i));
                    if (&seed_packet == &wall_nut_packet)
                        add_plant(WALLNUT, setting.plants_data[3].health, temp->get_block(i));
                    if (&seed_packet == &frozen_shooter_packet)
                        add_plant(FROZEN_PEASHOOTER, setting.plants_data[2].health, temp->get_block(i));
                    if (&seed_packet == &melon_packet)
                        add_plant(MELON, setting.plants_data[4].health, temp->get_block(i));
                    seed_packet.release();
                    seed_packet.reset_remaining_time();
                    sun_packet.spend_money(seed_packet.cost());
                    temp->get_block(i)->defaultlight_area();
                }
        if (!select_any_block && !select_packet)
            seed_packet.release();
    }
}


void Game::check_mouse_in_gameplay()
{
    if (event.type == Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == Mouse::Left)
        {
            Vector2i mouse_position = Mouse::getPosition(*window);
            bool sun_collected = click_suns((Vector2f)mouse_position);

            put_plant((Vector2f)mouse_position, sun_collected, sun_flower_packet);
            put_plant((Vector2f)mouse_position, sun_collected, wall_nut_packet);
            put_plant((Vector2f)mouse_position, sun_collected, shooter_packet);
            put_plant((Vector2f)mouse_position, sun_collected, frozen_shooter_packet);
            put_plant((Vector2f)mouse_position, sun_collected, melon_packet);
        }
    }
    else if (event.type == Event::MouseMoved)
        mouse_move();
}

void Game::check_mouse_click_in_menu()
{
    if (event.type == Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == Mouse::Left)
        {
            Vector2i mouse_position = Mouse::getPosition(*window);
            if (start_button.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
            {
                global_clock.restart();
                page = GAMEPLAY;
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

void Game::check_mouse_click()
{
    while (window->pollEvent(event))
    {
        if (event.type == Event::Closed)
            window->close();

        if (page == GAMEPLAY)
            check_mouse_in_gameplay();

        if (page == MENU)
            check_mouse_click_in_menu();
    }
}

bool Game::have_zombie_in_front(Plant *plant)
{
    for (Zombie *temp : zombies)
        if (temp->get_line() == plant->get_block()->get_line() && temp->get_sprite().getPosition().x + ZOMBIE_DISTANSE_FROM_SPRITE > plant->get_block()->get_position().x)
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
    Time interval_add_sun = seconds(setting.sun_data.vertical_speed);
    add_sun_time += add_sun_clock.restart();
    if (add_sun_time >= interval_add_sun)
    {
        suns.push_back(new Sun(RANDOM_POSITION_OF_SUN, setting.sun_data.vertical_speed));
        add_sun_time -= interval_add_sun;
    }
}

void Game::add_zombie()
{

    add_zombie_time += add_zombie_clock.restart();
    if (add_zombie_time >= interval_add_zombie)
    {
        if (rand() % 2)
            zombies.push_back(new Zombie(RANDOM_LINE, seconds(setting.zombies_data[0].speed), setting.zombies_data[0].health, setting.zombies_data[0].damage, REGULAR));
        else
            zombies.push_back(new Zombie(RANDOM_LINE, seconds(setting.zombies_data[1].speed), setting.zombies_data[1].health, setting.zombies_data[1].damage, ANGRY));
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
        plants.push_back(new Defender_Plant(health, block));
    if (type == SUNFLOWER)
        plants.push_back(new Sun_Plant(health, block, setting.sun_data.generate_speed));
    if (type == PEASHOOTER)
        plants.push_back(new Invasive_Plant(health, block, PEASHOOTER, seconds(setting.plants_data[1].hit_rate)));
    if (type == FROZEN_PEASHOOTER)
        plants.push_back(new Invasive_Plant(health, block, FROZEN_PEASHOOTER, seconds(setting.plants_data[2].hit_rate)));
    if (type == MELON)
        plants.push_back(new Invasive_Plant(health, block, MELON, seconds(setting.plants_data[4].hit_rate)));
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

void Game::render_melons()
{
    for (Melon *temp : melons)
    {
        window->draw(temp->get_sprite());
    }
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
void Game::render_line_plants(int line)
{
    for (Plant *temp : plants)
        if (temp->get_block()->get_line() == line)
            window->draw(temp->get_sprite());
}

void Game::render_plants()
{
    for (int i = 1; i <= 5; i++)
        render_line_plants(i);
}

void Game::render_previews()
{
    if (shooter_packet.selection_status())
        window->draw(shooter_packet.get_plant_sprite());
    if (frozen_shooter_packet.selection_status())
        window->draw(frozen_shooter_packet.get_plant_sprite());
    if (sun_flower_packet.selection_status())
        window->draw(sun_flower_packet.get_plant_sprite());
    if (wall_nut_packet.selection_status())
        window->draw(wall_nut_packet.get_plant_sprite());
    if (melon_packet.selection_status())
        window->draw(melon_packet.get_plant_sprite());
}

void Game::render()
{
    window->clear();

    if (page == MENU)
    {
        window->draw(menu);
        window->draw(start_button);
    }
    if (page == GAMEPLAY)
    {
        window->draw(background);
        render_table();
        render_plants();
        render_zombies();
        render_packets();
        render_peas();
        render_melons();
        render_suns();
        render_previews();
    }
    if (page == LOSE || page == WIN)
        window->draw(background);

    window->display();
}

void Game::update_plants()
{
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
}

void Game::change_zombie_rate()
{
    Time interval_zombie_rate = seconds(setting.time_data.time_flag);
    zombie_rate_time += zombie_rate_clock.restart();
    if (zombie_rate_time >= interval_zombie_rate)
        if (interval_add_zombie.asSeconds() > 1)
        {
            interval_add_zombie = seconds(interval_add_zombie.asSeconds() - setting.time_data.decrease_duration_zombie_attack);
            zombie_rate_time -= interval_zombie_rate;
        }
}

void Game::update()
{
    check_mouse_click();
    if (page == MENU)
        if (main_sound.getStatus() == SoundSource::Stopped)
            main_sound.play();

    if (page == GAMEPLAY)
    {
        change_zombie_rate();
        add_zombie();
        update_packets();
        add_sun_from_top();

        update_plants();
        update_zombies();
        update_suns();
        update_peas();
        update_melons();

        check_collision();

        global_time += global_clock.restart();

        if (global_time >= seconds(setting.time_data.total_time))
        {
            page = WIN;
            main_sound.stop();
            win_sound.play();
        }
    }
    if (page == LOSE)
        background.setTexture(lose_texture);
    if (page == WIN)
        background.setTexture(win_texture);
}
