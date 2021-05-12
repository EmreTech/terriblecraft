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
struct Layer;
struct ChunkMesh;  

struct ChunkMeshBuilder
{
    ChunkMeshBuilder(Layer& chunk);

    void buildMesh(ChunkMesh& mesh);

    private:
    void addFace(const std::vector<float>& blockFace,
                const glm::vec2& textureCoords,
                const glm::vec3& blockPos,
                const glm::vec3& blockFacing);

    bool makeFace(const glm::vec3& blockPos);

    // TODO: Switch over to using full chunks for building chunk meshes
    Layer *pLayer = nullptr;
    ChunkMesh *pMesh = nullptr;
    const Block::BlockDataHolder* pBlockData = nullptr;
};

} // namespace Chunk

} // namespace World::Chunk


#endif