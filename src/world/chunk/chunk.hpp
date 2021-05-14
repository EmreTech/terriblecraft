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
  Chunk(const glm::vec2 &pos);

  void generate();

  void makeMesh(const Player::Camera &cam);

  void addLayer();
  void removeLayer(int y);

  void setBlock(int x, int y, int z, Block::Block b);
  Block::Block getBlock(int x, int y, int z) const noexcept;

  Layer &getLayer(int index);

  const glm::vec2 &getPosition() const;

private:
  bool yOutOfBound(int y) const noexcept;
  bool xzOutOfBound(int x, int z) const noexcept;
  bool outOfBounds(int x, int y, int z) const noexcept;

  std::vector<Layer> layers;
  glm::vec2 position;
  
  bool generated = false;
};

} // namespace Chunk

} // namespace World

#endif