#include "chunk.hpp"

#include "chunk_manager.hpp"
#include "../block/block_data.hpp"

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

Chunk::Chunk(const glm::vec3 &position, ChunkManager &manager)
: Position(position), mesh(position), ptManager(&manager)
{
    blocks.fill(BlockDataManager::get().getId(CommonBlock::Air));
}

block_t Chunk::quickGetBlock(const glm::vec3 &pos) const
{
    if (blockPosOutOfChunkBounds(pos))
        return BlockDataManager::get().getId(CommonBlock::Air);
    
    return blocks[toLocalIndex(pos)];
}

void Chunk::quickSetBlock(const glm::vec3 &pos, block_t block)
{
    if (blockPosOutOfChunkBounds(pos))
        return;

    blocks[toLocalIndex(pos)] = block;
}

block_t Chunk::getBlock(const glm::vec3 &pos) const
{
    if (blockPosOutOfChunkBounds(pos))
        return ptManager->getBlock(pos);

    return quickGetBlock(pos);
}

void Chunk::setBlock(const glm::vec3 &pos, block_t block)
{
    if (blockPosOutOfChunkBounds(pos))
    {
        ptManager->setBlock(pos, block);
        return;
    }

    quickSetBlock(pos, block);
}

const glm::vec3& Chunk::getPosition() const
{
    return Position;
}

ChunkMesh& Chunk::getMesh()
{
    return mesh;
}

} // namespace World
