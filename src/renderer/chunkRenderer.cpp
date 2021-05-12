#include "chunkRenderer.hpp"

#include <iostream>

namespace Renderer
{

ChunkRenderer::ChunkRenderer()
{
    atlasTexture.init("res/images/blocks.png", GL_RGBA, STBI_rgb_alpha);
}

void ChunkRenderer::add(const World::Chunk::ChunkMesh& mesh)
{
    chunks.push_back(&mesh);
}

void ChunkRenderer::render(const World::Player::Camera& cam)
{
    shader.activate();
    atlasTexture.bind();

    glm::mat4 projection = glm::perspective(
    glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 
    0.1f, 100.0f);

    shader.uniformMatrix4("projection", projection);
    shader.uniformMatrix4("view", cam.ViewMatrix());

    for (const World::Chunk::ChunkMesh* mesh : chunks)
    {
        mesh->getModel().vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

} // namespace Renderer