#include "block_manager.hpp"
#include "block.hpp"

namespace World::Block
{

block_t BlockManager::generateBlock(glm::vec3 pos, BlockType type)
{
    block_t id;

    if (blocks.empty())
        id = 0;
    
    else
    {
        block_t current_id = blocks.back().id;
        id = current_id + 1;
    }

    Block b;
    b.Position = pos;
    b.type = type;
    b.id = id;

    blocks.push_back(b);
    return id;
}

void BlockManager::deleteBlock(block_t id)
{
    bool blockExists = false;
    size_t indexForBlock;

    for (size_t i{0}; i < blocks.size(); i++)
    {
        uint8_t currentId = blocks.at(i).id;

        if (currentId == id)
        {
            indexForBlock = i;
            blockExists = true;
            break;
        }
    }

    if (blockExists)
        blocks.erase(blocks.begin() + (indexForBlock - 1));
    
}

Block BlockManager::getBlock(block_t id)
{
    bool blockExist = blockExists(id);

    if (blockExist)
    {
        Block output;
        for (Block b : blocks)
            if (b.id == id)
                output = b;
        return output;
    }
    
    Block output;
    output.isEmpty = true;
    return output;
}

block_t BlockManager::setBlock(Block &block)
{
    block_t id = block.id;

    if (id == '\0')
    {
        if (blocks.empty())
            id = 0;
        
        else
        {
            block_t current_id = blocks.back().id;
            id = current_id + 1;
        }

        block.id = id;
    }

    blocks.push_back(block);
    return id;   
}

bool BlockManager::blockExists(block_t id)
{
    bool blockExists = false;
    for (size_t i{0}; i < blocks.size(); i++)
    {
        block_t currentId = blocks.at(i).id;

        if (currentId == id)
        {
            blockExists = true;
            break;
        }
    }

    return blockExists;
}

} // namespace World::Block
