#include "chunkSection.hpp"

#include <iostream>

#include "chunkMeshBuilder.hpp"
#include "../world.hpp"

namespace World::Chunk {

ChunkSection::ChunkSection() 
{ 
  position = {0, 0, 0};
}

ChunkSection::ChunkSection(const glm::vec3& pos, World &world) : position(pos), ptWorld(&world)
{}

void ChunkSection::setBlock(int x, int y, int z, Block::Block b) {
  if (outOfBounds(x) || outOfBounds(y) || outOfBounds(z))
  {
    auto location = toWorldPosition(x, y, z);
    ptWorld->setBlock(location.x, location.y, location.z, b);
    return;
  }

  layers.at(y).update(b);
  blocks[getIndex(x, y, z)] = b;
}

Block::Block ChunkSection::getBlock(int x, int y, int z) const {
  if (outOfBounds(x) || outOfBounds(y) || outOfBounds(z))
  {
    auto location = toWorldPosition(x, y, z);
    return ptWorld->getBlock(location.x, location.y, location.z);
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

glm::vec3 ChunkSection::toWorldPosition(int x, int y, int z) const
{
  return {position.x * CHUNK_SIZE + x,
          position.y * CHUNK_SIZE + y,
          position.z * CHUNK_SIZE + z};
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
  if (y == -1)
  {
    return ptWorld->getChunk(position.x, position.z)
      .getSection(position.y - 1)
      .getLayer(CHUNK_SIZE - 1);
  }

  else if (y == CHUNK_SIZE)
  {
    return ptWorld->getChunk(position.x, position.z)
      .getSection(position.y + 1)
      .getLayer(0);
  }

  else
  {
    return layers.at(y);
  }
}

ChunkSection &ChunkSection::getAdjacent(int dx, int dz)
{
  int x = position.x + dx;
  int z = position.z + dz;

  return ptWorld->getChunk(x, z).getSection(position.y);
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
