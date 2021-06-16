#include "chunkRenderer.hpp"

#include "../world/world_constants.hpp"
#include "../world/chunk/chunk_mesh.hpp"
#include "../camera.hpp"

namespace Renderer
{

ChunkRenderer::ChunkRenderer()
{
    shader.init("shaders/chunkVertex.glsl", "shaders/chunkFragment.glsl");
    textureAtlas.init("res/images/blocks.png");
}

void ChunkRenderer::add(World::ChunkMesh &mesh)
{
    chunkMeshes.push_back(mesh.buffer());
}

void ChunkRenderer::render(const Camera &cam)
{
    glEnable(GL_DEPTH_TEST);

    shader.activate();
    textureAtlas.bind();
    shader.uniformMatrix4("projView", (cam.ProjMatrix() * cam.ViewMatrix()));

    for (auto &e : chunkMeshes)
    {
        e.getDrawable().bindDraw();
    }

    glDisable(GL_DEPTH_TEST);

    chunkMeshes.clear();
}

} // namespace Renderer
