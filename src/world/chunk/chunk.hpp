#ifndef CHUNK_HPP
#define CHUNK_HPP

#include <glm/vec2.hpp>

#include <vector>

#include "../../utils/singleton.hpp"
#include "chunkSection.hpp"

namespace Renderer
{
  struct ChunkRenderer;
} // namespace Renderer


namespace World::Chunk {

struct Chunk {
  Chunk() = default;
  Chunk(const glm::vec2 &pos);

  void makeMesh();
  void deleteMeshes();
  void draw(Renderer::ChunkRenderer& renderer);

  void addSection();
  void addSections(int index);
  void addSectionsInBlocks(int blockY);

  void removeSection(int y);

  void setBlock(int x, int y, int z, Block::Block b);
  Block::Block getBlock(int x, int y, int z) const noexcept;

  ChunkSection &getSection(int index);
  const glm::vec2 &getPosition() const;
  size_t getAmountOfSections() const;

private:
  bool yOutOfBound(int y) const noexcept;
  bool xzOutOfBound(int x, int z) const noexcept;
  bool outOfBounds(int x, int y, int z) const noexcept;

  std::vector<ChunkSection> chunks;
  glm::vec2 position;
  
  //bool generated = false;
};

} // namespace World::Chunk

#endif