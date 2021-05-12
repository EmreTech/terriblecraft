#ifndef LAYER_HPP
#define LAYER_HPP

#include <glm/vec3.hpp>

#include <array>

#include "chunkMesh.hpp"
#include "../block/block.hpp"
#include "../world_constants.hpp"

namespace World::Chunk {

struct Layer {
private:
  friend struct Chunk;

public:
  ChunkMesh mesh;

  Layer();

  void setBlock(int x, int z, Block::Block block);
  Block::Block getBlock(int x, int z) const;

  const glm::vec3 getPosition();

private:
  static bool outOfBounds(int val);
  int getIndex(int x, int z) const;

  std::array<Block::Block, CHUNK_AREA> blocks;

  glm::vec3 position;
};

} // namespace World::Chunk

#endif