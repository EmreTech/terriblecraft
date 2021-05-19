#include "chunkSection.hpp"

#include <iostream>

#include "chunkMeshBuilder.hpp"

namespace World::Chunk {

ChunkSection::ChunkSection() 
{ 
  position = {0, 0, 0};
}

ChunkSection::ChunkSection(const glm::vec3& pos) : position(pos) 
{}

void ChunkSection::setBlock(int x, int y, int z, Block::Block b) {
  if (outOfBounds(x) || outOfBounds(y) || outOfBounds(z))
  {
    return;
  }

  layers.at(y).update(b);
  blocks[getIndex(x, y, z)] = b;
}

Block::Block ChunkSection::getBlock(int x, int y, int z) const {
  if (outOfBounds(x) || outOfBounds(y) || outOfBounds(z))
  {
    return Block::BlockType::AIR;
  }

  return blocks.at(getIndex(x, y, z));
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

const ChunkSection::Layer& ChunkSection::getLayer(int y) const
{
  // TODO: Properly search for the right layer in the if-else statements below
  if (y == -1)
  {
    return layers.at(0);
  }

  else if (y == CHUNK_SIZE)
  {
    return layers.at(15);
  }

  else
  {
    return layers.at(y);
  }
}

void ChunkSection::deleteMeshes()
{
  if (hasMesh)
  {
    mesh.deleteData();
    hasMesh = false;
    bufferedMesh = false;
  }
}

bool ChunkSection::outOfBounds(int val) { 
  return val >= CHUNK_SIZE || val < 0; 
}

int ChunkSection::getIndex(int x, int y, int z) const { 
  return y * CHUNK_AREA + z * CHUNK_SIZE + x; 
}

} // namespace World::Chunk
