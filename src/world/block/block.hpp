#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>

#include "blockid.hpp"

namespace World::Block
{

/**
 * @brief Stores all data for a single block. This includes the position,
 * block type, mesh vertices (including texture coordinates), and its id.
 * 
 * Managed by the block manager.
 */
struct Block
{
    // Block's current position in the world
    glm::vec3 Position;
    
    // Block type
    BlockType type;

    // The block's id. Assigned by the block manager.
    uint8_t id;

    // A bool to check if the block is empty. Used by the block manager when it can't find a block with the same id.
    bool isEmpty = false;
};

} // namespace World::Block

#endif