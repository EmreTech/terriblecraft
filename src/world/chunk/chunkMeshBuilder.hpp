#ifndef CHUNK_MESH_BUILDER_HPP
#define CHUNK_MESH_BUILDER_HPP

#include <vector>

#include "../../utils/glm_include.hpp"

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

    /**
     * Builds a chunk mesh by looping through every single block in the Chunk Section.
     * It checks if a face points an air or non-opaque block, then adds to the mesh or not.
     */
    void buildMesh(ChunkMesh& mesh);

    private:
    /**
     * Attempts to add face vertices to a chunk mesh.
     */
    void addFace(const std::vector<float>& blockFace,
                const glm::vec2& textureCoords,
                const glm::vec3& blockPos,
                const glm::vec3& blockFacing);

    /**
     * Checks if the block face should be added to the mesh.
     * Ciertia:
     * - Block face is pointing towards an air block
     * - Block face is pointing towards a non-opaque block
     */
    bool makeFace(const glm::vec3& blockPos);

    ChunkSection *pChunk = nullptr;
    ChunkMesh *pMesh = nullptr;
    const Block::BlockDataHolder* pBlockData = nullptr;
};

} // namespace Chunk

} // namespace World::Chunk


#endif