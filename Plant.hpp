#pragma once

#include "Headers.hpp"

using namespace std;
using namespace sf;

class Plant
{
private:

    int health;
    string type;
    int pic_num = 0;

public:
    void getting_hit();

};