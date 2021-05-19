#ifndef CHUNK_SECTION_HPP
#define CHUNK_SECTION_HPP

#include <glm/vec3.hpp>

#include <array>

#include "chunkMesh.hpp"
#include "../block/block.hpp"
#include "../world_constants.hpp"

namespace World::Chunk {

struct ChunkSection {
private:
  friend struct Chunk;

  struct Layer
  {
    void update(Block::Block c)
    {
      if (c.getData().getData().isOpaque)
        solidBlocks--;
      else
        solidBlocks++;
    }

    bool isAllSolid() const
    {
      return solidBlocks == CHUNK_AREA;
    }

    private:
    int solidBlocks = 0;
  };

public:
  ChunkMesh mesh;

  ChunkSection();
  ChunkSection(const glm::vec3& pos);

  void setBlock(int x, int y, int z, Block::Block block);
  Block::Block getBlock(int x, int y, int z) const;

  const glm::vec3 getPosition() const;

  bool getHasMesh() const;
  bool buffered() const;

  const Layer& getLayer(int y) const;

  void makeMesh();
  void buffer();

  void deleteMeshes();

private:
  static bool outOfBounds(int val);
  int getIndex(int x, int y, int z) const;

  std::array<Block::Block, CHUNK_VOLUME> blocks;
  std::array<Layer, CHUNK_SIZE> layers;

  glm::vec3 position;
  bool hasMesh, bufferedMesh = false;
};

} // namespace World::Chunk

#endif