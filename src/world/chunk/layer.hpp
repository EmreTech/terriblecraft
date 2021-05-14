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
  Layer(const glm::vec3& pos);

  void setBlock(int x, int z, Block::Block block);
  Block::Block getBlock(int x, int z) const;

  const glm::vec3 getPosition() const;

  bool getHasMesh() const;
  bool buffered() const;

  void makeMesh();
  void buffer();

  void deleteMeshes();

  void setShouldGenerateTopFace(bool val);
  bool getShouldGenerateTopFace() const;

  void setShouldGenerateBottomFace(bool val);
  bool getShouldGenerateBottomFace() const;

private:
  static bool outOfBounds(int val);
  int getIndex(int x, int z) const;

  void generate();

  std::array<Block::Block, CHUNK_AREA> blocks;

  glm::vec3 position;
  bool hasMesh, bufferedMesh = false;

  bool topFace, bottomFace = false;
};

} // namespace World::Chunk

#endif