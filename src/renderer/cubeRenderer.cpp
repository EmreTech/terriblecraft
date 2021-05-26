#include "cubeRenderer.hpp"

#include "../camera.hpp"
#include "../utils/constants.hpp"

namespace Renderer
{

CubeRenderer::CubeRenderer()
{
    shader.init("shaders/basicVertex.glsl", "shaders/basicFragment.glsl");

    float vertices[] = {
        // Back
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.8f,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.8f, 
        1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.8f, 
        0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.8f,

        // Right
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.6f,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.6f,
        1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.6f,
        1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.6f,

        // Front
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.8f,
        0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.8f,
        0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.8f,
        1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.8f, 

        // Left
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.6f,
        0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.6f,
        0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.6f,
        0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.6f,

        // Top
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,

        // Bottom
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.4f,
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.4f,
        1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.4f,
        0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.4f,
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    vao.init();
    vbo.init(GL_ARRAY_BUFFER);
    ebo.init(GL_ELEMENT_ARRAY_BUFFER);

    vao.bind();
    vbo.bind(GL_ARRAY_BUFFER);
    vbo.bufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices);

    ebo.bind(GL_ELEMENT_ARRAY_BUFFER);
    ebo.bufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices);

    vao.attribute(vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    vao.attribute(vbo, 1, 2, GL_FLOAT, 6 * sizeof(float), 3 * sizeof(float));
    glEnableVertexAttribArray(1);

    vao.attribute(vbo, 2, 1, GL_FLOAT, 6 * sizeof(float), 5 * sizeof(float));
    glEnableVertexAttribArray(2);

    texture.init("res/images/blocks/grass_side.png", GL_RGBA, STBI_rgb_alpha);

    std::cout << glGetError() << '\n';
}

CubeRenderer::~CubeRenderer()
{
    vbo.destroy();
    ebo.destroy();
    vao.destroy();
}

void CubeRenderer::add(const glm::vec3 &position)
{
    cubePos.push_back(position);
}

void CubeRenderer::render(const Camera &cam)
{
    glEnable(GL_DEPTH_TEST);
    texture.bind();

    shader.activate();

    auto projection = cam.ProjMatrix();
    auto view = cam.ViewMatrix();
    shader.uniformMatrix4("projView", (projection * view));

    vao.bind();
    for (auto &position : cubePos)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position);
        shader.uniformMatrix4("model", model);

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
    }

    glDisable(GL_DEPTH_TEST);
    cubePos.clear();
}

} // namespace Renderer
