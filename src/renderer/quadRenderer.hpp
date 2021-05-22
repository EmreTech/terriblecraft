#ifndef QUAD_RENDERER_HPP
#define QUAD_RENDERER_HPP

#include <string>

//#include "../utils/glm_include.hpp"
#include "../gl/shader.hpp"
#include "../gl/buffer.hpp"
#include "../gl/vao.hpp"

namespace Renderer
{

struct QuadRenderer
{
    QuadRenderer();
    ~QuadRenderer();

    void render();

    private:
    gl::Shader shader;

    gl::Buffer vbo;
    gl::Buffer ebo;
    gl::VAO vao;
};

} // namespace Renderer

#endif