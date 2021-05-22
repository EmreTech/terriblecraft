#ifndef CHUNK_SECTION_HPP
#define CHUNK_SECTION_HPP

#include <glm/vec3.hpp>

#include <array>

#include "chunkMesh.hpp"
#include "../block/block.hpp"
#include "../world_constants.hpp"

namespace World {

struct World;

namespace Chunk {

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
  ChunkSection(const glm::vec3& pos, World &world);

  void setBlock(int x, int y, int z, Block::Block block);
  Block::Block getBlock(int x, int y, int z) const;

  const glm::vec3 getPosition() const;

  bool getHasMesh() const;
  bool buffered() const;

  const Layer& getLayer(int y) const;
  ChunkSection &getAdjacent(int dx, int dz);

  void makeMesh();
  void buffer();

  void deleteMeshes();

private:
  glm::vec3 toWorldPosition(int x, int y, int z) const;

  static bool outOfBounds(int val);
  int getIndex(int x, int y, int z) const;

  std::array<Block::Block, CHUNK_VOLUME> blocks;
  std::array<Layer, CHUNK_SIZE> layers;

  glm::vec3 position;

  World *ptWorld = nullptr;
  bool hasMesh, bufferedMesh = false;
};

} // namespace Chunk

} // namespace World

#endif