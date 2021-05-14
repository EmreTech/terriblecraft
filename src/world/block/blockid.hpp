#ifndef BLOCKID_HPP
#define BLOCKID_HPP

#include <cstdint>

namespace World::Block {

typedef uint8_t block_t;

enum class BlockType : block_t {
  AIR,
  GRASS,
  FULL_GRASS,
  DIRT,
  STONE,

  SIZE_TYPES
};

} // namespace World::Block

#endif