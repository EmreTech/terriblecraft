#ifndef BLOCK_ID_HPP
#define BLOCK_ID_HPP

#include <stdint.h>

namespace World
{

typedef uint8_t block_t;

enum class BlockMeshStyle : uint8_t
{
    Block = 0,
    Cross,
    None,
};

enum class BlockType : uint8_t
{
    Solid = 0,
    Fluid,
    Plant,
    Gas,
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