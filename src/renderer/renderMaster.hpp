#ifndef RENDER_MASTER_HPP
#define RENDER_MASTER_HPP

#include <SFML/Window.hpp>

#include "quadRenderer.hpp"
#include "cubeRenderer.hpp"
#include "chunkRenderer.hpp"

struct Camera;

namespace World
{
struct Chunk;
} // namespace World

namespace Renderer
{

struct RenderMaster
{
    void drawQuad(const glm::vec3 &pos);
    void drawCube(const glm::vec3 &pos);
    void drawChunk(World::Chunk &chunk);

    void finishRender(const Camera &cam);

    private:
    QuadRenderer quadRenderer;
    CubeRenderer cubeRenderer;
    ChunkRenderer chunkRenderer;
};

} // namespace Renderer


#endif