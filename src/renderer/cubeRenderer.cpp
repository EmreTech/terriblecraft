#include "cubeRenderer.hpp"

#include <iostream>

#include "../world/player/camera.hpp"
#include "../utils/types.hpp"

std::vector<float> vecTwoToFloat(std::array<glm::vec2, 6> vec)
{
    std::vector<float> output;
    for (size_t i{0}; i < vec.size(); i++)
    {
        auto cx = vec.at(i).x;
        auto cy = vec.at(i).y;

        output.push_back(cx);
        output.push_back(cy);
    }
    return output;
}

namespace Renderer
{

CubeRenderer::CubeRenderer()
{
    atlasTexture.init("res/images/blocks.png", GL_RGBA, STBI_rgb_alpha);

    std::vector<float> vertex
    {
        // Back face
        -0.5f, -0.5f, -0.5f, // Bottom-left
        0.5f, 0.5f, -0.5f,   // top-right
        0.5f, -0.5f, -0.5f,  // bottom-right
        0.5f, 0.5f, -0.5f,   // top-right
        -0.5f, -0.5f, -0.5f, // bottom-left
        -0.5f, 0.5f, -0.5f,  // top-left
        // Front face
        -0.5f, -0.5f, 0.5f, // bottom-left
        0.5f, -0.5f, 0.5f,  // bottom-right
        0.5f, 0.5f, 0.5f,   // top-right
        0.5f, 0.5f, 0.5f,   // top-right
        -0.5f, 0.5f, 0.5f,  // top-left
        -0.5f, -0.5f, 0.5f, // bottom-left
        // Left face
        -0.5f, 0.5f, 0.5f,   // top-right
        -0.5f, 0.5f, -0.5f,  // top-left
        -0.5f, -0.5f, -0.5f, // bottom-left
        -0.5f, -0.5f, -0.5f, // bottom-left
        -0.5f, -0.5f, 0.5f,  // bottom-right
        -0.5f, 0.5f, 0.5f,   // top-right
        // Right face
        0.5f, 0.5f, 0.5f,    // top-left
        0.5f, -0.5f, -0.5f,  // bottom-right
        0.5f, 0.5f, -0.5f,   // top-right
        0.5f, -0.5f, -0.5f,  // bottom-right
        0.5f, 0.5f, 0.5f,    // top-left
        0.5f, -0.5f, 0.5f,   // bottom-left
        // Bottom face
        -0.5f, -0.5f, -0.5f, // top-right
        0.5f, -0.5f, -0.5f,  // top-left
        0.5f, -0.5f, 0.5f,   // bottom-left
        0.5f, -0.5f, 0.5f,   // bottom-left
        -0.5f, -0.5f, 0.5f,  // bottom-right
        -0.5f, -0.5f, -0.5f, // top-right
        // Top face
        -0.5f, 0.5f, -0.5f, // top-left
        0.5f, 0.5f, 0.5f,   // bottom-right
        0.5f, 0.5f, -0.5f,  // top-right
        0.5f, 0.5f, 0.5f,   // bottom-right
        -0.5f, 0.5f, -0.5f, // top-left
        -0.5f, 0.5f, 0.5f,  // bottom-left
    };

    auto back = vecTwoToFloat(World::Block::GetTextureCoords(1, 0, 0));
    auto front = vecTwoToFloat(World::Block::GetTextureCoords(1, 0, 1));
    auto left = vecTwoToFloat(World::Block::GetTextureCoords(1, 0, 2));
    auto right = vecTwoToFloat(World::Block::GetTextureCoords(1, 0, 3));
    auto bottom = vecTwoToFloat(World::Block::GetTextureCoords(2, 0, 4));
    auto top = vecTwoToFloat(World::Block::GetTextureCoords(0, 0, 5));

    std::vector<float> texCoords;
    texCoords.insert(texCoords.end(), back.begin(),   back.end()); // Back
    texCoords.insert(texCoords.end(), front.begin(),  front.end()); // Front
    texCoords.insert(texCoords.end(), left.begin(),   left.end()); // Left
    texCoords.insert(texCoords.end(), right.begin(),  right.end()); // Right
    texCoords.insert(texCoords.end(), bottom.begin(), bottom.end()); // Bottom
    texCoords.insert(texCoords.end(), top.begin(),    top.end()); // Top

    cubeModel.addMeshData({vertex, texCoords});
}

void CubeRenderer::add(const glm::vec3& pos)
{
    quads.push_back(pos);
}

void CubeRenderer::render(const World::Player::Camera& cam)
{
    shader.activate();
    cubeModel.vao.bind();
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

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

} // namespace Renderer
