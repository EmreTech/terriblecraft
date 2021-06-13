#ifndef CHUNK_RENDERER_HPP
#define CHUNK_RENDERER_HPP

#include <string>
#include <unordered_map>

#include "../gl/shader.hpp"
#include "../gl/vertex_array.hpp"
#include "../world/coordinate.hpp"

struct Camera;

namespace World
{
    struct ChunkMesh;
} // namespace World

namespace Renderer
{

struct ChunkRenderer
{
    ChunkRenderer() = default;

    void add(World::ChunkMesh &mesh);
    void render(const Camera &cam);

    private:
    std::unordered_map<glm::vec3, gl::VertexArray, PositionHash> chunkMeshes;

    gl::Shader shader{"shaders/chunkVertex.glsl", "shaders/basicFragment.glsl"};
};

} // namespace Renderer


#endif