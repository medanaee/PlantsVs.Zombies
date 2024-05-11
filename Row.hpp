#pragma once

#include "Headers.hpp"
#include "Block.hpp"

using namespace std;
using namespace sf;

class Row
{
private:
    vector<Block*> blocks;
    int line;
    
public:
    Row(Vector2f start_pos, int line);
    Block* get_block(int block_num);
};