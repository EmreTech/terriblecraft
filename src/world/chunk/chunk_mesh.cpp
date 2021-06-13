#include "chunk_mesh.hpp"

#include "../world_constants.hpp"

namespace
{

template <typename T>
size_t vectorSize(const std::vector<T> vec)
{
    return vec.size() * sizeof(vec[0]);
}

} // namespace

namespace World
{

ChunkMesh::ChunkMesh(const Position &chunkPos)
: position(chunkPos) {}

void ChunkMesh::addFace(const MeshFace &face, const Position &blockPos, const TextureData &textureCoords)
{
    TextureCoords.insert(TextureCoords.end(), textureCoords.begin(), textureCoords.end());

    int index = 0;
    for (unsigned int i = 0; i < 4; i++)
    {
        vertices.push_back(face.vertices[index++] + position.x * CHUNK_SIZE   + blockPos.x);
        vertices.push_back(face.vertices[index++] + position.y * CHUNK_HEIGHT + blockPos.y);
        vertices.push_back(face.vertices[index++] + position.z * CHUNK_SIZE   + blockPos.z);

        lightLevels.push_back(face.lightLevel);
    }

    indices.push_back(indicesCount);
    indices.push_back(indicesCount + 1);
    indices.push_back(indicesCount + 2);
    indices.push_back(indicesCount + 2);
    indices.push_back(indicesCount + 3);
    indices.push_back(indicesCount);
    indicesCount += 4;
}

gl::VertexArray ChunkMesh::buffer()
{
    gl::VertexArray vao;

    vao.addVBO(3, vertices);
    vao.addVBO(2, TextureCoords);
    vao.addVBO(1, lightLevels);
    
    vao.addEBO(indices);
    return vao;
}

size_t ChunkMesh::calculateBufferSize() const
{
    //return vectorSize(vertexData) + vectorSize(indices);
}

} // namespace World
