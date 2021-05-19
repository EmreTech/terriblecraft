#ifndef CHUNK_RENDERER_HPP
#define CHUNK_RENDERER_HPP

#include <string>
#include <vector>

#include "../gl/shader.hpp"
#include "../gl/texture.hpp"
#include "../world/player/camera.hpp"
#include "../world/chunk/chunkMesh.hpp"

struct RenderInfo;

namespace Renderer
{

struct ChunkRenderer
{
    ChunkRenderer();

    void add(const World::Chunk::ChunkMesh& mesh);
    void render(const World::Player::Camera& cam);

    private:
    std::vector<const RenderInfo *> chunks;

    gl::Texture atlasTexture;
    gl::Shader shader = gl::Shader("shaders/chunkVertex.glsl", "shaders/frag.glsl");
};

} // namespace Renderer


#endif