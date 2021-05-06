#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <glm/vec3.hpp>
#include <vector>

namespace World::Block
{

enum BlockType
{
    AIR,
    GRASS,
    DIRT,
    STONE,
};

struct Block
{
    // Block's current position in the world
    glm::vec3 Position;
    
    // Block type (will be set for children of this class)
    BlockType type;

    // The parent chunk the block is contained in
    // Chunk *ParentChunk;

    // The position vertices and texture coordinates for the block
    std::vector<float> vertices;

    Block(glm::vec3 pos/*, Chunk *parent_chunk*/) : Position{pos}/*, ParentChunk{parent_chunk}*/ {}
};

} // namespace World::Block

#endif