#include "Block.hpp"

RectangleShape Block::get_area(){return area;}
Vector2f Block::get_position()
{
    return area.getPosition();
}
void Block::highlight_area() { area.setFillColor(sf::Color(255, 255, 255, 50)); }
void Block::reset_area_color(){area.setFillColor(sf::Color(0,0,0,0));}

int Block::get_line()
{
    return line;
}

void Block::set_plant(Plant *plant)
{
    this->plant = plant;
}

Plant *Block::get_plant()
{
    return plant;
}

Block::Block(float position_x,float position_y, int line)
{
    //define BLOCK_LENGHT 87;
    //define BLOCK_WIDTH 108;
    area.setSize(sf::Vector2f(87,108));
    area.setPosition(position_x,position_y);
    area.setFillColor(sf::Color(0,0,0,0));
    this->line = line;
}