#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include <map>

#include "chunk/chunk.hpp"
#include "generation/terrainGeneration.hpp"
#include "player/camera.hpp"
#include "../renderer/chunkRenderer.hpp"

namespace World
{

using CompressedBlocks = std::vector<std::pair<uint16_t, uint32_t>>;

/**
 * Highly compresses a chunk by storing each block like this for example: Grass: 10.
 * 
 * @param Chunk The input chunk to compress
 * 
 * @return A CompressedBlocks object with the compressed chunk
 */
CompressedBlocks compressChunk(Chunk::Chunk& chunk);

/**
 * Decompresses a chunk by simply following the pattern in the CompressedBlocks that were provided.
 * 
 * @param blocks The compressed chunk
 * @param pos The compressed chunks position
 * 
 * @return A decompressed Chunk
 */
Chunk::Chunk decompressChunk(const CompressedBlocks& blocks, const glm::vec2& pos, World &world);

struct World
{
    using ChunkMap = std::map<glm::vec2, Chunk::Chunk>;
    using CompressedChunkMap = std::map<glm::vec2, CompressedBlocks>;

    World() = default;
    ~World();

    void setBlock(int x, int y, int z, Block::Block b);
    Block::Block getBlock(int x, int y, int z);

    Chunk::Chunk& getChunk(int x, int z);

    bool chunkLoadedAt(int x, int z) const;
    bool chunkUnloadedAt(int x, int z) const;
    bool chunkExistsAt(int x, int z) const;

    void loadChunk(int x, int z);
    void unloadChunk(int x, int z);

    void update();
    void updateChunk(int bX, int bY, int bZ);

    void makeMesh(int x, int z);
    void buffer(int x, int z);
    void deleteMeshes();

    void renderWorld(Renderer::ChunkRenderer &renderer, const Player::Camera &cam);

    static glm::vec2 getBlockXZ(int x, int z);
    static glm::vec2 getChunkXZ(int x, int z);

    private:
    void updateChunks();

    ChunkMap loadedChunks;
    CompressedChunkMap unloadedChunks;

    std::vector<glm::vec3> chunkUpdates;

    Generation::TerrainGenerator generator;

    bool isRunning = true;

    int loadDistance = 2;
    const int renderDistance = 6;
};

} // namespace World


#endif