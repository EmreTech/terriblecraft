#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "blockid.hpp"
#include "blockdata.hpp"

namespace World::Block {

struct Block {
  Block() = default;

  Block(block_t id);
  Block(BlockType id);

  const BlockData &getData() const;

  bool operator==(Block other) const { return id == other.id; }

  bool operator!=(Block other) const { return !(*this == other); }

  block_t id = static_cast<block_t>(BlockType::AIR);
};

} // namespace World::Block

#endif