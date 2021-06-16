#ifndef CHUNK_MANAGER_HPP
#define CHUNK_MANAGER_HPP

#include <unordered_map>

#include "chunk.hpp"
#include "../coordinate.hpp"

namespace World
{

struct ChunkManager final
{
    Chunk &addChunk(const Position &chunk);
    void removeChunk(const Position &chunk);
    Chunk &getChunk(const Position &chunk);

    block_t getBlock(const Position &pos) const;
    void setBlock(const Position &pos, block_t block);

    bool hasChunk(const Position &chunk) const;
    bool hasNeighbours(const Position &chunk) const;

    void ensureNeighbours(const Position &chunkPos);

    private:
    std::unordered_map<Position, Chunk, PositionHash> chunks;
};

} // namespace World


#endif