#ifndef QUAD_RENDERER_HPP
#define QUAD_RENDERER_HPP

#include <string>
#include <vector>

//#include "../utils/glm_include.hpp"
#include "../gl/shader.hpp"
#include "../gl/buffer.hpp"
#include "../gl/vao.hpp"

struct Camera;

namespace Renderer
{

struct QuadRenderer
{
    QuadRenderer();
    ~QuadRenderer();

    void add(const glm::vec3 &position);
    void render(const Camera &cam);

    private:
    std::vector<glm::vec3> quadPos;

    gl::Shader shader;

    gl::Buffer vbo;
    gl::Buffer ebo;
    gl::VAO vao;
};

} // namespace Renderer

#endif