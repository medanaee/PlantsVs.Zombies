#pragma once

#include "Headers.hpp"
#include "Plant.hpp"
class Plant;

using namespace std;
using namespace sf;

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
    void reset_area_color();
    int get_line();
    void set_plant(Plant* plant);
    Plant* get_plant();
};

