#ifndef RENDER_MASTER_HPP
#define RENDER_MASTER_HPP

#include <SFML/Window.hpp>

#include "quadRenderer.hpp"

struct Camera;

namespace Renderer
{

struct RenderMaster
{
    void drawQuad(const glm::vec3 &pos);
    void finishRender(const Camera &cam);

    private:
    QuadRenderer quadRenderer;
};

} // namespace Renderer


#endif