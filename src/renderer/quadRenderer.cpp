#include "quadRenderer.hpp"

#include "../camera.hpp"
#include "../utils/constants.hpp"

namespace Renderer
{

QuadRenderer::QuadRenderer()
{
    shader.init("shaders/basicVertex.glsl", "shaders/basicFragment.glsl");

    float vertices[] = {
        // Positions         // Texture Coords
        -0.5f,  0.5f, 0.0f,  0.0f, 0.0f, // top right
         0.5f,  0.5f, 0.0f,  1.0f, 0.0f, // bottom right
         0.5f, -0.5f, 0.0f,  1.0f, 1.0f, // bottom left
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, // top left
    };

    unsigned int indices[] = {
        0, 1, 2, // First Triangle
        2, 3, 0, // Second Triangle
    };

    vao.init();
    vbo.init(GL_ARRAY_BUFFER);
    ebo.init(GL_ELEMENT_ARRAY_BUFFER);

    vao.bind();
    vbo.bind(GL_ARRAY_BUFFER);
    vbo.bufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices);

    ebo.bind(GL_ELEMENT_ARRAY_BUFFER);
    ebo.bufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices);

    vao.attribute(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    vao.attribute(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), 3 * sizeof(float));
    glEnableVertexAttribArray(1);

    texture.init("res/images/container.jpg", GL_RGB, STBI_rgb);
}

QuadRenderer::~QuadRenderer()
{
    vbo.destroy();
    ebo.destroy();
    vao.destroy();
}

void QuadRenderer::add(const glm::vec3 &position)
{
    quadPos.push_back(position);
}

void QuadRenderer::render(const Camera &cam)
{
    texture.bind();

    shader.activate();
    vao.bind();
    
    auto projection = cam.ProjMatrix();
    auto view = cam.ViewMatrix();

    shader.uniformMatrix4("projView", (projection * view));

    for (auto &position : quadPos)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position);
        
        shader.uniformMatrix4("model", model);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }

    quadPos.clear();
}

} // namespace Renderer
