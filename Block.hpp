#include "Zombie.hpp"

class Block
{
private:
    RectangleShape area;
    Plant* plant; 
    
    
public:
    Block(float position_x,float position_y);
    RectangleShape get_area();
    void highlight_area();
    void reset_area_color();
   
};

