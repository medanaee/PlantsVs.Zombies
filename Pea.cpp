#include "Pea.hpp"

Pea::Pea(string type)
{
    if(type == "regular")
    {
        image.loadFromFile("./Pics/Main Items/Pea.png");
        sprite.setTexture(image);
    }

    else if (type == "freezed")
    {
        /* code */
    }
    
}

void Pea::update()
{
    
}
