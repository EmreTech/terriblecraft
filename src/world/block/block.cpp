#include "block.hpp"

#include "blockdatabase.hpp"

namespace World::Block {

Block::Block(block_t id) : id(id) {}
Block::Block(BlockType id) : id(static_cast<block_t>(id)) {}

const BlockData &Block::getData() const {
  return BlockDatabase::getInstance().getData(static_cast<BlockType>(id));
}

} // namespace World::Block
