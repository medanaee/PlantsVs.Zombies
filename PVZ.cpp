#include "Headers.hpp"
#include "Game.hpp"

using namespace std;
using namespace sf;

int main()
{
    game pvz;
    while (pvz.running())
    {
        pvz.update();
        pvz.render();
    }
}