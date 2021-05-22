#include "world.hpp"

namespace glm
{

// Fixes a compiler error
bool operator<(const vec2& first, const vec2& second)
{
  return (first.x < second.x) && (first.y < second.y);
}

} // namespace glm


namespace World
{

CompressedBlocks compressChunk(Chunk::Chunk& chunk)
{
  CompressedBlocks output;
  Block::Block currentBlock = chunk.getBlock(0, 0, 0);
  uint32_t blockCount = 1;

  for (uint32_t i = 1; i < (CHUNK_VOLUME * chunk.getAmountOfSections()); i++)
  {
	int x = i % CHUNK_SIZE;
	int y = i / CHUNK_AREA;
	int z = (i / CHUNK_SIZE) % CHUNK_SIZE;

	auto block = chunk.getBlock(x, y, z);

	if (block == currentBlock)
	  blockCount++;

	else
	{
	  output.emplace_back(currentBlock.id, blockCount);
	  currentBlock = block;
	  blockCount = 1;
	}
  }

  output.emplace_back(currentBlock.id, blockCount);
  return output;
}

Chunk::Chunk decompressChunk(const CompressedBlocks& blocks, const glm::vec2& pos, World &world)
{
  Chunk::Chunk output(pos, world);
  int blockPointer = 0;

  for (auto& block : blocks)
  {
	auto blockType = block.first;
	auto count = block.second;

	for (uint32_t i = 0; i < count; i++)
	{
	  int x = blockPointer % CHUNK_SIZE;
	  int y = blockPointer / CHUNK_AREA;
	  int z = (blockPointer / CHUNK_SIZE) % CHUNK_SIZE;

	  output.setBlock(x, y, z, blockType);
	  blockPointer++;
	}
  }

  return output;
}

World::~World()
{
    isRunning = false;
}

void World::setBlock(int x, int y, int z, Block::Block b)
{
    if (y <= 0)
        return;

    auto blockPos = getBlockXZ(x, z);
    auto chunkPos = getChunkXZ(x, z);

    getChunk(chunkPos.x, chunkPos.y).setBlock(blockPos.x, y, blockPos.y, b);
}

Block::Block World::getBlock(int x, int y, int z)
{
    auto blockPos = getBlockXZ(x, z);
    auto chunkPos = getChunkXZ(x, z);

    return getChunk(chunkPos.x, chunkPos.y).getBlock(blockPos.x, y, blockPos.y);
}


Chunk::Chunk& World::getChunk(int x, int z)
{
    glm::vec2 key(x, z);

    if (!chunkExistsAt(x, z))
    {
        Chunk::Chunk chunk{key, *this};
        loadedChunks[key] = std::move(chunk);
    }
    
    if (chunkLoadedAt(x, z))
        return loadedChunks.at(key);

    else if (chunkUnloadedAt(x, z))
    {
        static Chunk::Chunk chunk = decompressChunk(unloadedChunks.at(key), key, *this);
        return chunk;
    }
}

bool World::chunkLoadedAt(int x, int z) const
{
    return loadedChunks.find(glm::vec2{x, z}) != loadedChunks.end();
}

bool World::chunkUnloadedAt(int x, int z) const
{
    return unloadedChunks.find(glm::vec2{x, z}) != unloadedChunks.end();
}

bool World::chunkExistsAt(int x, int z) const
{
    return chunkLoadedAt(x, z) || chunkUnloadedAt(x, z);
}

void World::loadChunk(int x, int z)
{
  auto chunk = getChunk(x, z);

  if (chunk.hasLoaded() && chunkUnloadedAt(x, z))
  {
    loadedChunks.insert({chunk.getPosition(), chunk});
    unloadedChunks.erase(chunk.getPosition());
    return;
  }

  getChunk(x, z).load(generator);
}

void World::unloadChunk(int x, int z)
{
  if (!chunkLoadedAt(x, z) || chunkUnloadedAt(x, z))
    return;

  auto chunk = getChunk(x, z);
  unloadedChunks.insert({chunk.getPosition(), compressChunk(chunk)});
  loadedChunks.erase(chunk.getPosition());
}

void World::update()
{
    updateChunks();
}

void World::updateChunk(int bx, int by, int bz)
{
  auto addChunkToUpdate = [&](const glm::vec3& key)
  {
    chunkUpdates.push_back(key);
  };

  auto chunkPos = getChunkXZ(bx, bz);
  auto chunkSecY = by / CHUNK_SIZE;

  glm::vec3 key(chunkPos.x, chunkSecY, chunkPos.y);
  addChunkToUpdate(key);

  auto sectionBlockXZ = getBlockXZ(bx, bz);
  auto sectionBlockY = by % CHUNK_SIZE;

  /**
   * The following if-else if statements are to ensure that all surrounding chunk meshes are updated.
   * If not, then there would be holes in the world if you break blocks near chunk borders.
   */

  if (sectionBlockXZ.x == 0)
  {
    key.x -= 1;
    addChunkToUpdate(key);
  }
  else if (sectionBlockXZ.x == CHUNK_SIZE - 1)
  {
    key.x += 1;
    addChunkToUpdate(key);
  }

  if (sectionBlockY == 0)
  {
    key.y -= 1;
    addChunkToUpdate(key);
  }
  else if (sectionBlockY == CHUNK_SIZE - 1)
  {
    key.y += 1;
    addChunkToUpdate(key);
  }

  if (sectionBlockXZ.y == 0)
  {
    key.z -= 1;
    addChunkToUpdate(key);
  }
  else if (sectionBlockXZ.y == CHUNK_SIZE - 1)
  {
    key.z += 1;
    addChunkToUpdate(key);
  }
}

void World::updateChunks()
{
  for (auto& e : chunkUpdates)
  {
    auto &sec = getChunk(e.x, e.z).getSection(e.y);

    sec.deleteMeshes();
    sec.makeMesh();
  }
  chunkUpdates.clear();
}

void World::makeMesh(int x, int z)
{
  for (int nx = -1; nx <= 1; nx++)
  for (int nz = -1; nz <= 1; nz++)
    loadChunk(x + nx, z + nz);

  getChunk(x, z).makeMesh();
}

void World::deleteMeshes()
{
  for (auto& chunk : loadedChunks)
    chunk.second.deleteMeshes();
}

void World::renderWorld(Renderer::ChunkRenderer &renderer, const Player::Camera &cam)
{
  for (auto itr = loadedChunks.begin(); itr != loadedChunks.end(); itr++)
  {
    Chunk::Chunk &chunk = itr->second;

    int camX = cam.Position.x;
    int camZ = cam.Position.z;

    int minX = (camX / CHUNK_SIZE) - renderDistance;
    int minZ = (camZ / CHUNK_SIZE) - renderDistance;
    int maxX = (camX / CHUNK_SIZE) + renderDistance;
    int maxZ = (camZ / CHUNK_SIZE) + renderDistance;

    auto loc = chunk.getPosition();

    /*if (minX > loc.x || minZ > loc.y || maxZ < loc.y || maxX < loc.x)
    {
      auto movingChunk = std::move(loadedChunks.extract(itr).mapped());

      unloadedChunks.insert({loc, compressChunk(movingChunk)});
      itr = loadedChunks.erase(itr);

      continue;
    }
    else
    {
      chunk.draw(renderer);
      itr++;
    }*/

    chunk.draw(renderer);
  }
}

glm::vec2 World::getBlockXZ(int x, int z)
{
  return {x % CHUNK_SIZE, z % CHUNK_SIZE};
}

glm::vec2 World::getChunkXZ(int x, int z)
{
  return {x / CHUNK_SIZE, z / CHUNK_SIZE};
}


} // namespace World
