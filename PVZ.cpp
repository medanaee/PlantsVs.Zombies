#include "Headers.hpp"
#include "Game.hpp"

using namespace std;
using namespace sf;

int main()
{
    game pvz;
    // for(int i = 0; i < 5; i++)
    // {
    //     pvz.add_pea("FROZEN", i + 1, 50, 20);
    // }
    // pvz.add_1zombie();
    

    while (pvz.running())
    {
        pvz.update();
        pvz.render();
    }
}