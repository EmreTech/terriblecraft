#ifndef BLOCKID_HPP
#define BLOCKID_HPP

#include <cstdint>

namespace World::Block
{

typedef uint8_t block_t;

enum BlockType : block_t
{
    AIR,
    GRASS,
    DIRT,
    STONE,
};

} // namespace World::Block


#endif