#ifndef SKYBOX_RENDERER_HPP
#define SKYBOX_RENDERER_HPP

#include <string>
#include <vector>

#include "../gl/shader.hpp"
#include "../gl/vao.hpp"
#include "../gl/buffer.hpp"
#include "../world/player/camera.hpp"

namespace Renderer
{

struct SkyboxRenderer
{
    SkyboxRenderer();
    ~SkyboxRenderer();

    void render(const World::Player::Camera& cam);

    private:
    unsigned int cubemapID;
    gl::Shader shader = gl::Shader("shaders/skyVertex.glsl", "shaders/skyFrag.glsl");

    gl::VAO vao;
    gl::Buffer vbo;
};

} // namespace Renderer


#endif