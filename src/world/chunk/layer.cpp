#include "layer.hpp"

#include <iostream>

#include "chunkMeshBuilder.hpp"

namespace World::Chunk {

Layer::Layer() 
{ 
  position = {0, 0, 0};
  generate();
}

Layer::Layer(const glm::vec3& pos) : position(pos) 
{
  generate();
}

void Layer::setBlock(int x, int z, Block::Block b) {
  if (outOfBounds(x) || outOfBounds(z))
  {
    return;
  }

  auto index = getIndex(x, z);
  blocks[index] = b;
}

Block::Block Layer::getBlock(int x, int z) const {
  if (outOfBounds(x) || outOfBounds(z))
  {
    return Block::BlockType::AIR;
  }

  auto index = getIndex(x, z);
  return blocks[index];
}

const glm::vec3 Layer::getPosition() const { return position; }

bool Layer::getHasMesh() const
{
  return hasMesh;
}

bool Layer::buffered() const
{
  return bufferedMesh;
}

void Layer::makeMesh()
{
  ChunkMeshBuilder(*this).buildMesh(mesh);
  hasMesh = true;
  bufferedMesh = true;
}

void Layer::buffer()
{
  mesh.buffer();
  bufferedMesh = true;
}

void Layer::deleteMeshes()
{
  if (hasMesh)
  {
    bufferedMesh = false;
    hasMesh = false;
    mesh.deleteData();
  }
}

void Layer::setShouldGenerateTopFace(bool val)
{
  topFace = val;
}
bool Layer::getShouldGenerateTopFace() const
{
  return topFace;
}
void Layer::setShouldGenerateBottomFace(bool val)
{
  bottomFace = val;
}
bool Layer::getShouldGenerateBottomFace() const
{
  return bottomFace;
}

bool Layer::outOfBounds(int val) { return val >= CHUNK_SIZE || val < 0; }

int Layer::getIndex(int x, int z) const { return x + z; }

void Layer::generate()
{
  for (int x = 0; x < CHUNK_SIZE; x++)
  for (int z = 0; z < CHUNK_SIZE; z++)
  {
    setBlock(x, z, Block::BlockType::AIR);
  }
}

} // namespace World::Chunk
