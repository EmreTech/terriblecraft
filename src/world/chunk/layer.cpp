#include "layer.hpp"

#include <iostream>

namespace World::Chunk {

Layer::Layer() { position = {0, 0, 0}; }

void Layer::setBlock(int x, int z, Block::Block b) {
  if (outOfBounds(x) || outOfBounds(z))
  {
    std::cout << "Out of bounds!" << '\n';
    return;
  }

  auto index = getIndex(x, z);
  blocks[index] = b;
}

Block::Block Layer::getBlock(int x, int z) const {
  if (outOfBounds(x) || outOfBounds(z))
  {
    std::cout << "Out of bounds!" << '\n';
    return Block::BlockType::AIR;
  }

  auto index = getIndex(x, z);
  return blocks[index];
}

const glm::vec3 Layer::getPosition() { return position; }

bool Layer::outOfBounds(int val) { return val >= CHUNK_SIZE || val < 0; }

int Layer::getIndex(int x, int z) const { return x + z; }

} // namespace World::Chunk
