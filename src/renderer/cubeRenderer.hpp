#ifndef CUBE_RENDERER_HPP
#define CUBE_RENDERER_HPP

#include <string>
#include <vector>

#include "../gl/shader.hpp"
#include "../gl/buffer.hpp"
#include "../gl/vao.hpp"
#include "../gl/texture.hpp"

struct Camera;

namespace Renderer
{

struct CubeRenderer
{
    CubeRenderer();
    ~CubeRenderer();

    void add(const glm::vec3 &position);
    void render(const Camera &cam);

    private:
    std::vector<glm::vec3> cubePos;

    gl::Shader shader;

    gl::Buffer vbo, ebo;
    gl::VAO vao;

    gl::Texture texture;
};

} // namespace Renderer

#endif