#ifndef BLOCKDATABASE_HPP
#define BLOCKDATABASE_HPP

#include <array>
#include <memory>

#include "../../utils/singleton.hpp"
#include "blockid.hpp"

namespace World::Block {

struct BlockData;

struct BlockDatabase : public Singleton {
  static BlockDatabase &getInstance();
  const BlockData &getData(BlockType id) const;

private:
  BlockDatabase();

  std::array<std::unique_ptr<BlockData>, (size_t)BlockType::SIZE_TYPES> blocks;
};

} // namespace World::Block

#endif