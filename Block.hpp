#pragma once

#include "Headers.hpp"
#include "Plant.hpp"

using namespace std;
using namespace sf;


class Plant;

class Block
{
private:
    RectangleShape area;
    Plant* plant = nullptr;
    int line;
    
public:
    Block(float position_x,float position_y, int line);
    RectangleShape get_area();
    Vector2f get_position();
    void highlight_area();
    void defaultlight_area();
    int get_line();
    void put_plant(Plant* plant);
    Plant* get_plant();
};

