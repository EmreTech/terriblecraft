#include "quadRenderer.hpp"

namespace Renderer
{

QuadRenderer::QuadRenderer()
{
    shader.init("shaders/basicVertex.glsl", "shaders/basicFragment.glsl");

    float vertices[] = {
        -0.5f,  0.5f, 0.0f,  // top right
         0.5f,  0.5f, 0.0f,  // bottom right
         0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, -0.5f, 0.0f,  // top left
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

    vao.attribute(vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
}

QuadRenderer::~QuadRenderer()
{
    vbo.destroy();
    ebo.destroy();
    vao.destroy();
}

void QuadRenderer::render()
{
    shader.activate();
    vao.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

} // namespace Renderer
