#ifndef CUBE_RENDERER_HPP
#define CUBE_RENDERER_HPP

#include <string>

#include "../model.hpp"
#include "../gl/shader.hpp"
#include "../gl/texture.hpp"
#include "../world/block/blockatlas.hpp"
#include "../world/player/camera.hpp"

struct RenderInfo;

namespace Renderer
{

struct CubeRenderer
{
    CubeRenderer();

    void add(const glm::vec3& pos);
    void render(const World::Player::Camera& cam);

    private:
    std::vector<glm::vec3> quads;

    Model cubeModel;
    gl::Shader shader = gl::Shader("shaders/vertex.glsl", "shaders/frag.glsl");
    gl::Texture atlasTexture;
};

} // namespace Renderer


#endif