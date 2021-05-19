#include "chunkMesh.hpp"

#include <iostream>

#include "../world_constants.hpp"

namespace World::Chunk
{

void ChunkMesh::addFace(const std::vector<float>& faceVertices, 
                const std::vector<float>& textureCoords,
                const glm::vec3& chunkPos,
                const glm::vec3& blockPos,
                bool isTopBottom)
{
    faces++;
    mesh.textureCoords.insert(mesh.textureCoords.end(), textureCoords.begin(), textureCoords.end());

    for (int i = 0, index = 0; i < 4; i++)
    {
        mesh.vertexPositions.push_back(faceVertices[index++] + chunkPos.x * CHUNK_SIZE + blockPos.x);
        mesh.vertexPositions.push_back(faceVertices[index++] + chunkPos.y * CHUNK_SIZE + blockPos.y);
        mesh.vertexPositions.push_back(faceVertices[index++] + chunkPos.z * CHUNK_SIZE + blockPos.z);
    }

    mesh.indices.insert(mesh.indices.end(),
    {
        indicesIndex,
        indicesIndex + 1,
        indicesIndex + 2,
        indicesIndex + 2,
        indicesIndex + 3,
        indicesIndex
    }
    );

    indicesIndex += 4;
}

void ChunkMesh::buffer()
{
    model.addMeshData(mesh);

    mesh.vertexPositions.clear();
    mesh.textureCoords.clear();
    mesh.indices.clear();

    mesh.vertexPositions.shrink_to_fit();
    mesh.textureCoords.shrink_to_fit();
    mesh.indices.shrink_to_fit();

    indicesIndex = 0;
}

const Model& ChunkMesh::getModel() const
{
    return model;
}

void ChunkMesh::deleteData()
{
    model.deleteData();
}

} // namespace World::Chunk

