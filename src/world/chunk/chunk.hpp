#ifndef CHUNK_HPP
#define CHUNK_HPP

#include <glm/vec2.hpp>

#include <vector>

#include "../../utils/singleton.hpp"
#include "chunkSection.hpp"

namespace World::Chunk {

struct Chunk {
  Chunk() = default;
  Chunk(const glm::vec2 &pos);

  void generate();

  void makeMesh();
  void buffer();

  void addSection();
  void removeSection(int y);

  void setBlock(int x, int y, int z, Block::Block b);
  Block::Block getBlock(int x, int y, int z) const noexcept;

  ChunkSection &getSection(int index);

  const glm::vec2 &getPosition() const;

private:
  bool yOutOfBound(int y) const noexcept;
  bool xzOutOfBound(int x, int z) const noexcept;
  bool outOfBounds(int x, int y, int z) const noexcept;

  std::vector<ChunkSection> chunks;
  glm::vec2 position;
  
  bool generated = false;
};

} // namespace World::Chunk

#endif