#include "chunkSection.hpp"

#include <iostream>

#include "chunkMeshBuilder.hpp"

namespace World::Chunk {

ChunkSection::ChunkSection() 
{ 
  position = {0, 0, 0};
  generate();
}

ChunkSection::ChunkSection(const glm::vec3& pos) : position(pos) 
{
  generate();
}

void ChunkSection::setBlock(int x, int y, int z, Block::Block b) {
  if (outOfBounds(x) || outOfBounds(y) || outOfBounds(z))
  {
    return;
  }

  layers[y].update(b);
  auto index = getIndex(x, y, z);
  blocks[index] = b;
}

Block::Block ChunkSection::getBlock(int x, int y, int z) const {
  if (outOfBounds(x) || outOfBounds(y) || outOfBounds(z))
  {
    return Block::BlockType::AIR;
  }

  auto index = getIndex(x, y, z);
  return blocks[index];
}

const glm::vec3 ChunkSection::getPosition() const { return position; }

bool ChunkSection::getHasMesh() const
{
  return hasMesh;
}

bool ChunkSection::buffered() const
{
  return bufferedMesh;
}

void ChunkSection::makeMesh()
{
  if (!hasMesh)
  {
    ChunkMeshBuilder(*this).buildMesh(mesh);
    hasMesh = true;
  }
}

void ChunkSection::buffer()
{
  if (!bufferedMesh)
  {
    mesh.buffer();
    bufferedMesh = true;
  }
}

void ChunkSection::deleteMeshes()
{
  if (hasMesh)
  {
    bufferedMesh = false;
    hasMesh = false;
    mesh.deleteData();
  }
}

void ChunkSection::setShouldGenerateTopFace(bool val)
{
  topFace = val;
}
bool ChunkSection::getShouldGenerateTopFace() const
{
  return topFace;
}
void ChunkSection::setShouldGenerateBottomFace(bool val)
{
  bottomFace = val;
}
bool ChunkSection::getShouldGenerateBottomFace() const
{
  return bottomFace;
}

bool ChunkSection::outOfBounds(int val) { 
  return val >= CHUNK_SIZE || val < 0; 
}

int ChunkSection::getIndex(int x, int y, int z) const { 
  return y * CHUNK_AREA + z * CHUNK_SIZE + x; 
}

void ChunkSection::generate()
{
  for (int y = 0; y < CHUNK_SIZE; y++)
  for (int x = 0; x < CHUNK_SIZE; x++)
  for (int z = 0; z < CHUNK_SIZE; z++)
  {
    setBlock(x, y, z, Block::BlockType::AIR);
    Layer layer;
    layers[y] = layer;
  }
}

} // namespace World::Chunk
