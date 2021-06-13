#include "chunk.hpp"

namespace
{
    
bool blockPosOutOfChunkBounds(const glm::vec3 &position)
{
    return
    position.x < 0 || position.x >= CHUNK_SIZE ||
    position.y < 0 || position.y >= CHUNK_HEIGHT ||
    position.z < 0 || position.z >= CHUNK_SIZE;
}

int toLocalIndex(const glm::vec3 &pos)
{
    return pos.y * (CHUNK_AREA) + pos.z * CHUNK_SIZE + pos.x;
}

} // namespace


namespace World
{

Chunk::Chunk(const glm::vec3 &position)
: Position(position), mesh(position)
{}

block_t Chunk::quickGetBlock(const glm::vec3 &pos) const
{
    assert(!blockPosOutOfChunkBounds(pos));
    return blocks[toLocalIndex(pos)];
}

void Chunk::quickSetBlock(const glm::vec3 &pos, block_t block)
{
    assert(!blockPosOutOfChunkBounds(pos));
    blocks[toLocalIndex(pos)] = block;
}

block_t Chunk::getBlock(const glm::vec3 &pos) const
{
    if (blockPosOutOfChunkBounds(pos))
    {
        //TODO: When a world or chunk manager is implemented, use that to
        // get a block at the out-of-bounds position.
        return 0;
    }

    return quickGetBlock(pos);
}

void Chunk::setBlock(const glm::vec3 &pos, block_t block)
{
    if (blockPosOutOfChunkBounds(pos))
    {
        // TODO: When a world or chunk manager is implemented, use that to
        // set a block at the out-of-bounds position.
        return;
    }

    quickSetBlock(pos, block);
}

const glm::vec3& Chunk::getPosition() const
{
    return Position;
}

} // namespace World
