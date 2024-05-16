#include "Headers.hpp"
#include "Game.hpp"
#include "Setting.hpp"

using namespace std;
using namespace sf;

int main()
{
    Setting setting = extractor_setting();
    Game pvz(setting);


    while (pvz.running())
    {
        pvz.update();
        pvz.render();
    }
}