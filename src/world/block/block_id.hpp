#ifndef BLOCK_ID_HPP
#define BLOCK_ID_HPP

#include <stdint.h>

namespace World
{

typedef uint8_t block_t;

enum class BlockMeshStyle : uint8_t
{
    Block = 0, // Normal block style
    Cross, // Cross (aka X-shaped mesh), used for plants
    None, // None, used for gasses like air
};

enum class BlockType : uint8_t
{
    Solid = 0, // Solid block type, which is fully collidable 
    Fluid, // Fluid block type, which isn't collidable, but has interesting physics
    Plant, // Plant block type, not collidable
    Gas, // Gas block type, not collidable
};

enum class CommonBlock : block_t
{
    Air = 0,
    Stone,
    Sand,
    Water,

    Size
};

} // namespace World


#endif