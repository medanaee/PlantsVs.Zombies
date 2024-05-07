#include "Block.hpp"

Block::Block(float position_x,float position_y)
{
    area.setSize(sf::Vector2f(87,108));
    area.setPosition(position_x,position_y);
    area.setFillColor(sf::Color(0,0,0,0));
    

}

RectangleShape Block::get_area()
{
    return area;
}

void Block::highlight_area()
{
    area.setFillColor(sf::Color(255,255,255,50));
}

void Block::reset_area_color()
{
    area.setFillColor(sf::Color(0,0,0,0));
}
