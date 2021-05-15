#ifndef CHUNK_MESH_BUILDER_HPP
#define CHUNK_MESH_BUILDER_HPP

#include <glm/glm.hpp>

#include <vector>

namespace World
{

namespace Block
{
struct BlockDataHolder;
} // namespace Block


namespace Chunk
{
struct ChunkSection;
struct ChunkMesh;  

struct ChunkMeshBuilder
{
    ChunkMeshBuilder(ChunkSection& chunk);

    void buildMesh(ChunkMesh& mesh);

    private:
    void addFace(const std::vector<float>& blockFace,
                const glm::vec2& textureCoords,
                const glm::vec3& blockPos,
                const glm::vec3& blockFacing);

    bool makeFace(const glm::vec3& blockPos);

    ChunkSection *pChunk = nullptr;
    ChunkMesh *pMesh = nullptr;
    const Block::BlockDataHolder* pBlockData = nullptr;
};

} // namespace Chunk

} // namespace World::Chunk


#endif