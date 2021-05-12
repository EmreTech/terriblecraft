#ifndef CHUNKMESH_HPP
#define CHUNKMESH_HPP

#include "../../model.hpp"

namespace World::Chunk
{

struct ChunkMesh
{
    ChunkMesh();

    void addFace(const std::vector<float>& faceVertices, 
                const std::vector<float>& textureCoords,
                const glm::vec3& chunkPos,
                const glm::vec3& blockPos);

    void buffer();

    const Model& getModel() const;

    private:
    Mesh mesh;
    Model model;
};

} // namespace World::Chunk

#endif