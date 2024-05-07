#include "Row.hpp"

Row::Row(Vector2f start_pos)
{
    for(int i = 0; i < 9; i++)
    {
        blocks.push_back(new Block(start_pos.x + i * 87, start_pos.y));
    }
}

Block *Row::get_block(int block_num)
{
    return blocks[block_num];
}
