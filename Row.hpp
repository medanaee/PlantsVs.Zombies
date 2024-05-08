#pragma once

#include "Headers.hpp"
#include "Block.hpp"

using namespace std;
using namespace sf;

class Row
{
private:
    vector<Block*> blocks;
public:
    Row(Vector2f start_pos);
    Block* get_block(int block_num);

};

