#ifndef BLOCK_MANAGER_HPP
#define BLOCK_MANAGER_HPP

#include <glm/vec3.hpp>

#include <vector>
#include <utility>

#include "blockid.hpp"

namespace World::Block
{

struct Block;

struct BlockManager
{
    /**
     * @brief Generates a new block in the global list of blocks.
     * 
     * @param pos: The new block's position.
     * @param type: The new block's type.
     * 
     * @return The new block's id
     */
    static block_t generateBlock(glm::vec3 pos, BlockType type);

    /**
     * @brief Deletes a block in the global list of blocks. 
     * Checking is done to see if this block exists. If not, the function doesn't do anything.
     * 
     * @param id: The block's id
     */
    static void deleteBlock(block_t id);

    /**
     * @brief Gets a block from the global list of blocks.
     * 
     * @param id: The block's id
     * 
     * @return A copy of the block with the id. Empty block if not found.
     */
    static Block getBlock(block_t id);

    /**
     * @brief Sets a new block from an existing one.
     * This function is different from generateBlock, since it takes in an existing block.
     * 
     * @param block: A pointer to the block being set
     * 
     * @return The id of the newly added block
     */
    static block_t setBlock(Block &block);

    static bool blockExists(block_t id);

    private:
    static std::vector<Block> blocks;
};

} // namespace World::Block

#endif