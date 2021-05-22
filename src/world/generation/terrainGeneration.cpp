#include "terrainGeneration.hpp"

#include <algorithm>
#include <iostream>

#include "../chunk/chunk.hpp"

namespace World::Generation
{

void TerrainGenerator::generateTerrainFor(Chunk::Chunk &chunk)
{
    ptChunk = &chunk;
    setBlocks(0);
}

int TerrainGenerator::getMinimumSpawnHeight() const noexcept
{
    return CHUNK_SIZE * 4;
}

int TerrainGenerator::heightAt(int x, int z)
{
    auto chunkPosition = ptChunk->getPosition();

    float xCoord = (x + (chunkPosition.x * CHUNK_SIZE)) * 0.1f;
    float zCoord = (z + (chunkPosition.y * CHUNK_SIZE)) * 0.1f;

    auto noise = PerlinNoise::getInstance().generateNoise(xCoord * 1.5f, zCoord * 1.5f, 0) * 10.0f;
    return noise;
}

void TerrainGenerator::setBlocks(int max)
{
    for (int y = 0; y < CHUNK_SIZE * 2; y++)
    for (int x = 0; x < CHUNK_SIZE; x++)
    for (int z = 0; z < CHUNK_SIZE; z++)
    {
        if (y <= (CHUNK_SIZE - 1))
            ptChunk->setBlock(x, y, z, Block::BlockType::DIRT);

        if (y > (CHUNK_SIZE - 1))
        {
            int currentHeight = heightAt(x, z);
            float baseLandHeight = CHUNK_SIZE + 4.0f + currentHeight;

            Block::Block b;
            if (y <= baseLandHeight)
            {
                b = Block::BlockType::DIRT;

                if (y > baseLandHeight - 1)
                    b = Block::BlockType::GRASS;
            }

            ptChunk->setBlock(x, y, z, b);
        }
    }
}

} // namespace World::Generation