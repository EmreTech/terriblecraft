#ifndef CHUNKMESH_HPP
#define CHUNKMESH_HPP

#include "../../utils/glm_include.hpp"
#include "../../model.hpp"

namespace World::Chunk
{

struct ChunkMesh
{
    ChunkMesh() = default;

    void addFace(const std::vector<float>& faceVertices, 
                const std::vector<float>& textureCoords,
                const glm::vec3& chunkPos,
                const glm::vec3& blockPos,
                bool isTopBottom = false);

    void buffer();

    const Model& getModel() const;
    void deleteData();

    int faces = 0;

    private:
    Mesh mesh;
    Model model;
    unsigned int indicesIndex = 0;
};

} // namespace World::Chunk

#endif