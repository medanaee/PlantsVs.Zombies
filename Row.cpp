#include "Row.hpp"

Block *Row::get_block(int block_num){return blocks[block_num];}

Row::Row(Vector2f start_pos, int line)
{
    for(int i = 0; i < 9; i++)
        blocks.push_back(new Block(start_pos.x + i * BLOCK_LENGHT, start_pos.y, line));
}