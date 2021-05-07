#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>

namespace World::Block
{

enum BlockType
{
    NONE,
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
    BlockType type = NONE;

    // The position vertices for the block
    std::vector<float> position_vertices;

    // The texture coordinates for the block
    std::vector<glm::vec2> texture_coords;

    // Combined positional vertices and texture coordinates
    std::vector<float> full_vertices;

    Block(){}
    Block(glm::vec3 pos) : Position{pos}{}
};

} // namespace World::Block

#endif