#include "Headers.hpp"
#include "Game.hpp"

using namespace std;
using namespace sf;

int main()
{
    game pvz;
    pvz.add_pea("freezed", Vector2f(10,20));
    while (pvz.running())
    {
        pvz.update();
        pvz.render();
    }
}