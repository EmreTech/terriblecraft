#ifndef RENDER_MASTER_HPP
#define RENDER_MASTER_HPP

#include <SFML/Window.hpp>

#include "quadRenderer.hpp"
#include "cubeRenderer.hpp"

struct Camera;

namespace Renderer
{

struct RenderMaster
{
    void drawQuad(const glm::vec3 &pos);
    void drawCube(const glm::vec3 &pos);

    void finishRender(const Camera &cam);

    private:
    QuadRenderer quadRenderer;
    CubeRenderer cubeRenderer;
};

} // namespace Renderer


#endif