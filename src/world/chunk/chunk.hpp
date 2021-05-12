#ifndef CHUNK_HPP
#define CHUNK_HPP

#include <glm/vec2.hpp>

#include <vector>

#include "../../utils/singleton.hpp"
#include "layer.hpp"

namespace World {

namespace Player {
struct Camera;
} // namespace Player

namespace Chunk {

struct Chunk {
  Chunk() = default;
  Chunk(const glm::vec2 &position);

  bool makeMesh(const Player::Camera &cam);

  void setBlock(int x, int y, int z, Block::Block b);
  Block::Block getBlock(int x, int y, int z) const noexcept;

  Layer &getLayer(int y) { return layers.at(y); }

  const glm::vec2 &getPosition() const;

private:
  std::vector<Layer> layers;
  glm::vec2 position;
};

} // namespace Chunk

} // namespace World

#endif