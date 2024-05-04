#include "Game.hpp"

int main()
{
    game pvz;
    pvz.add_zombie();
    while (pvz.running())
    {
        pvz.update();
        pvz.render();
    }
}