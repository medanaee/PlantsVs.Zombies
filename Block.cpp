#include "Block.hpp"

Plant *Block::get_plant() { return plant; }
RectangleShape Block::get_area() { return area; }
Vector2f Block::get_position() { return area.getPosition(); }
int Block::get_line() { return line; }
void Block::highlight_area() { area.setFillColor(sf::HIGHLIGHT_COLOR); }
void Block::defaultlight_area() { area.setFillColor(sf::DEFAULT_COLOR); }
void Block::put_plant(Plant *plant) { this->plant = plant; }

Block::Block(float position_x, float position_y, int line)
{
    area.setSize(sf::Vector2f(BLOCK_LENGHT, BLOCK_WIDTH));
    area.setPosition(position_x, position_y);
    area.setFillColor(sf::DEFAULT_COLOR);
    this->line = line;
}