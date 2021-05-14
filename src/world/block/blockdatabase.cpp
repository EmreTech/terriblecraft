#include "blockdatabase.hpp"

#include "blockdata.hpp"

namespace World::Block {

BlockDatabase::BlockDatabase() {
  blocks[(size_t)BlockType::AIR] = std::make_unique<BlockData>  ("air");
  blocks[(size_t)BlockType::GRASS] = std::make_unique<BlockData>("grass");
  blocks[(size_t)BlockType::FULL_GRASS] = std::make_unique<BlockData>("full_grass");
  blocks[(size_t)BlockType::DIRT] = std::make_unique<BlockData> ("dirt");
  blocks[(size_t)BlockType::STONE] = std::make_unique<BlockData>("stone");
}

BlockDatabase &BlockDatabase::getInstance() {
  static BlockDatabase b;
  return b;
}

const BlockData &BlockDatabase::getData(BlockType id) const {
  return *blocks[(size_t)id];
}

} // namespace World::Block