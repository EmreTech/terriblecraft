#include "chunkMesh.hpp"

#include <iostream>

#include "../world_constants.hpp"

namespace World::Chunk
{

ChunkMesh::ChunkMesh(){}

void ChunkMesh::addFace(const std::vector<float>& faceVertices, 
                const std::vector<float>& textureCoords,
                const glm::vec3& chunkPos,
                const glm::vec3& blockPos)
{
    auto& vertices = mesh.vertexPositions;
    auto& texCoords = mesh.textureCoords;

    //for (size_t i = 0; i < textureCoords.size(); i++)
    //    std::cout << "Current texture coords data: " << textureCoords[i] << '\n';
    

    texCoords.insert(texCoords.end(), textureCoords.begin(), textureCoords.end());

    for (int i = 0, index = 0; i < 6; i++)
    {
        //std::cout << "Current vertex data: " << faceVertices[index] << '\n';

        vertices.push_back(faceVertices[index++] + chunkPos.x * CHUNK_SIZE + blockPos.x);
        vertices.push_back(faceVertices[index++] + chunkPos.y * CHUNK_SIZE + blockPos.y);
        vertices.push_back(faceVertices[index++] + chunkPos.z * CHUNK_SIZE + blockPos.z);
    }
}

void ChunkMesh::buffer()
{
    model.addMeshData(mesh);

    mesh.vertexPositions.clear();
    mesh.textureCoords.clear();

    mesh.vertexPositions.shrink_to_fit();
    mesh.textureCoords.shrink_to_fit();
}

const Model& ChunkMesh::getModel() const
{
    return model;
}

} // namespace World::Chunk

