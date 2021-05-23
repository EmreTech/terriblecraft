#include "renderMaster.hpp"

#include "../camera.hpp"

namespace Renderer
{

void RenderMaster::drawQuad(const glm::vec3 &pos)
{
    quadRenderer.add(pos);
}

void RenderMaster::finishRender(const Camera &cam)
{
    quadRenderer.render(cam);
}

} // namespace Renderer
