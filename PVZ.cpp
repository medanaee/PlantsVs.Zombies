#include "Headers.hpp"
#include "Game.hpp"
#include "Setting.hpp"

using namespace std;
using namespace sf;

int main()
{
    Setting setting = extractor_setting();
    cout<<setting.sun_data.money<<endl;
    Game pvz(setting);
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