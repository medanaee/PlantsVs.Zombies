#include "Block.hpp"

class Row
{
private:
    vector<Block*> blocks;
public:
    Row(Vector2f start_pos);
    Block* get_block(int block_num);

};

