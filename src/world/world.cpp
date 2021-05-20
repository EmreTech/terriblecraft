#include "world.hpp"

namespace World
{

/*CompressedBlocks compressChunk(Chunk::Chunk& chunk)
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

Chunk::Chunk decompressChunk(const CompressedBlocks& blocks, const glm::vec2& pos)
{
  Chunk::Chunk output(pos);
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
        Chunk::Chunk chunk{{x, z}};
        loadedChunks.emplace(key, std::move(chunk));
    }

    if (chunkLoadedAt(x, z))
        return loadedChunks.at(key);

    else if (chunkUnloadedAt(x, z))
    {
        static Chunk::Chunk chunk = decompressChunk(unloadedChunks.at(key), key);
        return chunk;
    }
}

bool World::chunkLoadedAt(int x, int z) const
{
    return loadedChunks.find({x, z}) != loadedChunks.end();
}

bool World::chunkUnloadedAt(int x, int z) const
{
    return unloadedChunks.find({x, z}) != unloadedChunks.end();
}

bool World::chunkExistsAt(int x, int z) const
{
    return chunkLoadedAt(x, z) || chunkUnloadedAt(x, z);
}

void World::update()
{
    updateChunks();
}*/

} // namespace World
