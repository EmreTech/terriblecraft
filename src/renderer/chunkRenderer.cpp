#include "chunkRenderer.hpp"

#include "../world/world_constants.hpp"
#include "../world/chunk/chunk_mesh.hpp"
#include "../camera.hpp"

namespace Renderer
{

void ChunkRenderer::add(World::ChunkMesh &mesh)
{
    chunkMeshes.emplace(std::make_pair(mesh.position, mesh.buffer()));
}

void ChunkRenderer::render(const Camera &cam)
{
    if (chunkMeshes.empty())
        return;

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    for (auto &e : chunkMeshes)
    {
        e.second.getDrawable().bindDraw();
    }

    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);

    chunkMeshes.clear();
}

} // namespace Renderer
