#ifndef TERRAIN_GENERATION_HPP
#define TERRAIN_GENERATION_HPP

#include <array>

#include "../../utils/perlin_noise.hpp"
#include "../world_constants.hpp"

namespace World
{

namespace Chunk
{

struct Chunk;

} // namespace Chunk

namespace Generation
{

struct TerrainGenerator
{
    TerrainGenerator() = default;
    
    void generateTerrainFor(Chunk::Chunk &chunk);
    int getMinimumSpawnHeight() const noexcept;

    private:
    int heightAt(int x, int z);
    void setBlocks(int max);

    Chunk::Chunk *ptChunk = nullptr;
};

} // namespace Generation

} // namespace World

#endif