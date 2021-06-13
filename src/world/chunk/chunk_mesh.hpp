#ifndef CHUNK_MESH_HPP
#define CHUNK_MESH_HPP

#include <array>

#include "../../gl/vertex_array.hpp"
#include "../coordinate.hpp"

namespace World
{

using VertexData = std::array<GLbyte, 12>;
using TextureData = std::array<float, 8>;

struct MeshFace
{
    VertexData vertices;
    GLbyte lightLevel;
};

struct ChunkMesh
{
    ChunkMesh(const Position &chunkPos);

    void addFace(const MeshFace &face, const Position &blockPos, const TextureData &textureCoords);

    gl::VertexArray buffer();
    size_t calculateBufferSize() const;

    Position position;

    std::vector<float> vertices;
    std::vector<float> TextureCoords;
    std::vector<GLuint> lightLevels;

    std::vector<unsigned int> indices;

    int indicesCount = 0;
};

} // namespace World


#endif