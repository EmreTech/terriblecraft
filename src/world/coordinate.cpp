#include "coordinate.hpp"

#include "world_constants.hpp"

size_t PositionHash::operator()(const Position &position) const
{
    return ((int) position.x * 88339) ^ ((int) position.z * 91967) ^ ((int) position.z * 126323);
}

Position worldToChunkPosition(const Position &position)
{
    return toChunkPosition(toBlockPosition(position));
}

Position toChunkPosition(const Position &position)
{
    int x = static_cast<int>(position.x);
    int y = static_cast<int>(position.y);
    int z = static_cast<int>(position.z);

    return
    {
        x < 0 ? ((x - CHUNK_SIZE) / CHUNK_SIZE) : (x / CHUNK_SIZE),
        y < 0 ? ((y - CHUNK_HEIGHT) / CHUNK_HEIGHT) : (y / CHUNK_HEIGHT),
        z < 0 ? ((z - CHUNK_SIZE) / CHUNK_SIZE) : (z / CHUNK_SIZE)
    };
}

Position toLocalBlockPosition(const Position &position)
{
    int x = static_cast<int>(position.x);
    int y = static_cast<int>(position.y);
    int z = static_cast<int>(position.z);

    return {(CHUNK_SIZE + (x % CHUNK_SIZE)) % CHUNK_SIZE,
            (CHUNK_HEIGHT + (y % CHUNK_HEIGHT)) % CHUNK_HEIGHT,
            (CHUNK_SIZE + (z % CHUNK_SIZE)) % CHUNK_SIZE};
}

Position toGlobalBlockPosition(const Position &blockPos, const Position &localChunkPos)
{
    return {localChunkPos.x * CHUNK_SIZE + blockPos.x,
            localChunkPos.y * CHUNK_HEIGHT + blockPos.y,
            localChunkPos.z * CHUNK_SIZE + blockPos.z};
}

Position toBlockPosition(const Position &vec)
{
    int x = static_cast<int>(glm::floor(vec.x));
    int y = static_cast<int>(glm::floor(vec.y)); 
    int z = static_cast<int>(glm::floor(vec.z)); 
    return {x, y, z};
}