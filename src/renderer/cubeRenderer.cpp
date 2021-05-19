#include "cubeRenderer.hpp"

#include <iostream>

#include "../world/player/camera.hpp"
#include "../utils/types.hpp"
#include "renderInfo.hpp"

namespace Renderer
{

CubeRenderer::CubeRenderer()
{
    atlasTexture.init("res/images/blocks.png", GL_RGBA, STBI_rgb_alpha);

    std::vector<float> vertex
    {
        //Back
        1, 0, 0,
        0, 0, 0,
        0, 1, 0,
        1, 1, 0,

        //Front
        0, 0, 1,
        1, 0, 1,
        1, 1, 1,
        0, 1, 1,

        //Right
        1, 0, 1,
        1, 0, 0,
        1, 1, 0,
        1, 1, 1,

        //Left
        0, 0, 0,
        0, 0, 1,
        0, 1, 1,
        0, 1, 0,

        //Top
        0, 1, 1,
        1, 1, 1,
        1, 1, 0,
        0, 1, 0,

        //Bottom
        0, 0, 0,
        1, 0, 0,
        1, 0, 1,
        0, 0, 1
    };

    auto top = World::Block::GetTextureCoords(0, 0);
    auto side = World::Block::GetTextureCoords(1, 0);
    auto bottom = World::Block::GetTextureCoords(2, 0);

    std::vector<float> texCoords;
    texCoords.insert(texCoords.end(), side.begin(),     side.end()); // Back
    texCoords.insert(texCoords.end(), side.begin(),     side.end()); // Front
    texCoords.insert(texCoords.end(), side.begin(),     side.end()); // Right
    texCoords.insert(texCoords.end(), side.begin(),     side.end()); // Left
    texCoords.insert(texCoords.end(), top.begin(),      top.end()); // Top
    texCoords.insert(texCoords.end(), bottom.begin(),   bottom.end()); // Bottom

    std::vector<GLuint> indices
    {
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

    cubeModel.addMeshData({vertex, texCoords, indices});
}

void CubeRenderer::add(const glm::vec3& pos)
{
    quads.push_back(pos);
}

void CubeRenderer::render(const World::Player::Camera& cam)
{
    shader.activate();
    cubeModel.getRenderInfo().vao.bind();
    atlasTexture.bind();

    glm::mat4 projection = glm::perspective(
    glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 
    0.1f, 100.0f);

    shader.uniformMatrix4("projection", projection);
    shader.uniformMatrix4("view", cam.ViewMatrix());

    for (auto& quad : quads)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, quad);
        shader.uniformMatrix4("model", model);

        glDrawElements(GL_TRIANGLES, cubeModel.getIndicesCount(), GL_UNSIGNED_INT, NULL);
    }
}

} // namespace Renderer
