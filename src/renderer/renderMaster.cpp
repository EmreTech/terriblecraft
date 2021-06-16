#include "renderMaster.hpp"

#include "../camera.hpp"
#include "../world/chunk/chunk.hpp"
#include "../world/chunk/chunk_mesh_builder.hpp"

namespace Renderer
{

void RenderMaster::drawQuad(const glm::vec3 &pos)
{
    quadRenderer.add(pos);
}

void RenderMaster::drawCube(const glm::vec3 &pos)
{
    cubeRenderer.add(pos);
}

void RenderMaster::drawChunk(World::Chunk &chunk)
{
    World::ChunkMesh mesh = World::buildChunkMesh(chunk);
    chunkRenderer.add(mesh);
}

void RenderMaster::finishRender(const Camera &cam)
{
    //quadRenderer.render(cam);
    cubeRenderer.render(cam);
    chunkRenderer.render(cam);
}

} // namespace Renderer
