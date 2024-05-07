#include "Game.hpp"

int main()
{
    game pvz;
    while (pvz.running())
    {
        pvz.update();
        pvz.render();
    }
}