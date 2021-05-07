#ifndef BLOCKATLAS_HPP
#define BLOCKATLAS_HPP

#include <glm/glm.hpp>

#include <iostream>
#include <array>

namespace World::Block
{

std::array<glm::vec2, 4> GetTextureCoords(int column, int row)
{
    const float maxColumn = 16.0f;
    const float maxRow = 16.0f;

    float leftX   = column                / maxColumn; // left_U
    float rightX  = (column + 1.0f)       / maxColumn; // right_U
    float topY    = (maxRow - row)        / maxRow; // top_V
    float bottomY = (maxRow - row - 1.0f) / maxRow; // bottom_V

    //std::cout << "Left X: " << leftX << " Right X: " << rightX <<
    //'\n' << "Top Y: " << topY << " Bottom Y: " << bottomY << '\n';

    return {
        glm::vec2(leftX, topY),
        glm::vec2(rightX, topY),
        glm::vec2(rightX, bottomY),
        glm::vec2(leftX, bottomY)
    };
}

} // namespace World::Block


#endif