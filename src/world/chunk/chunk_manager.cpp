#include "chunk_manager.hpp"

namespace World
{

Chunk& ChunkManager::addChunk(const Position &chunk)
{
    auto itr = chunks.find(chunk);
    if (itr == chunks.end())
    {
        return chunks.emplace(std::make_pair(chunk, Chunk{chunk})).first->second;
    }
    return itr->second;
}

const Chunk &ChunkManager::getChunk(const Position &chunk)
{
    auto itr = chunks.find(chunk);
    if (itr == chunks.end())
    {
        static Chunk c{{0, 0, 0}};
        return c;
    }
    return itr->second;
}

block_t ChunkManager::getBlock(const Position &pos) const
{
    auto chunkPos = toChunkPosition(pos);
    auto itr = chunks.find(chunkPos);
    if (itr == chunks.cend())
        return 0;

    return itr->second.quickGetBlock(toLocalBlockPosition(pos));
}

void ChunkManager::setBlock(const Position &pos, block_t block)
{
    auto chunkPos = toChunkPosition(pos);
    auto itr = chunks.find(chunkPos);
    auto local = toLocalBlockPosition(pos);

    if (itr != chunks.cend())
        itr->second.quickSetBlock(local, block);
    else
        addChunk(chunkPos).quickSetBlock(local, block);
}

bool ChunkManager::hasChunk(const Position &chunk) const
{
    return chunks.find(chunk) != chunks.cend();
}

} // namespace World
