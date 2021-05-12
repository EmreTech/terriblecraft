#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "blockid.hpp"

namespace World::Block {

struct BlockData;

struct Block {
  Block() = default;

  Block(block_t id);
  Block(BlockType id);

  const BlockData &getData() const;

  bool operator==(Block other) const { return id == other.id; }

  bool operator!=(Block other) const { return !(*this == other); }

  block_t id = 0;
};

} // namespace World::Block

#endif