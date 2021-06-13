#include "cubeRenderer.hpp"

#include <algorithm>
#include <iterator>

#include "../camera.hpp"
#include "../utils/constants.hpp"

namespace Renderer
{

CubeRenderer::CubeRenderer()
{
    shader.init("shaders/basicVertex.glsl", "shaders/basicFragment.glsl");

    std::vector<float> vertices {
        0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 
        1.0f, 0.0f, 0.0f, 
        0.0f, 0.0f, 0.0f,

        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f,

        1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,

        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f,

        1.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,

        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
    };

    /*

    0, 0 is bottom left
    1, 0 is bottom right
    1, 1 is top right
    0, 1 is top left

    */

    glm::vec2 bottomLeft (0.0f, 0.0f);
    glm::vec2 bottomRight(1.0f, 0.0f);
    glm::vec2 topRight(1.0f, 1.0f);
    glm::vec2 topLeft(0.0f, 1.0f);

    std::vector<float> texCoords;

    for (int i = 0; i < 6; i++)
    {
        texCoords.push_back(-bottomLeft.x);
        texCoords.push_back(bottomLeft.y);
        texCoords.push_back(-bottomRight.x);
        texCoords.push_back(bottomRight.y);

        texCoords.push_back(-topRight.x);
        texCoords.push_back(topRight.y);
        texCoords.push_back(-topLeft.x);
        texCoords.push_back(topLeft.y);
    }

    std::vector<float> lightLevs {
        0.8f,
        0.8f,
        0.8f,
        0.8f,

        0.6f,
        0.6f,
        0.6f,
        0.6f,

        0.8f,
        0.8f,
        0.8f,
        0.8f,

        0.6f,
        0.6f,
        0.6f,
        0.6f,

        1.0f,
        1.0f,
        1.0f,
        1.0f,

        0.4f,
        0.4f,
        0.4f,
        0.4f,
    };

    std::vector<GLuint> indices {
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

    nVAO.addVBO(3, vertices);
    nVAO.addVBO(2, texCoords);
    nVAO.addVBO(1, lightLevs);
    nVAO.addEBO(indices);

    texture.init("res/images/blocks.png");
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

    shader.uniformMatrix4("projView", (cam.ProjMatrix() * cam.ViewMatrix()));

    for (auto &position : cubePos)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position);
        shader.uniformMatrix4("model", model);

        nVAO.getDrawable().bindDraw();
    }

    glDisable(GL_DEPTH_TEST);
    cubePos.clear();
}

} // namespace Renderer
