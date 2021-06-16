#ifndef CHUNK_RENDERER_HPP
#define CHUNK_RENDERER_HPP

#include <string>
#include <vector>

#include "../gl/shader.hpp"
#include "../gl/texture.hpp"
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
    ChunkRenderer();

    void add(World::ChunkMesh &mesh);
    void render(const Camera &cam);

    private:
    std::vector<gl::VertexArray> chunkMeshes;

    gl::Shader shader;
    gl::Texture textureAtlas;
};

} // namespace Renderer


#endif