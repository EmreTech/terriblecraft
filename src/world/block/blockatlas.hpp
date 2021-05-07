#ifndef BLOCKATLAS_HPP
#define BLOCKATLAS_HPP

#include <glm/glm.hpp>

#include <iostream>
#include <array>

namespace World::Block
{

std::array<glm::vec2, 6> GetTextureCoords(int column, int row, int face)
{
    const float maxColumn = 16.0f;
    const float maxRow = 16.0f;

    float leftX   = column                / maxColumn; // left_U
    float rightX  = (column + 1.0f)       / maxColumn; // right_U
    float topY    = (maxRow - row)        / maxRow; // top_V
    float bottomY = (maxRow - row - 1.0f) / maxRow; // bottom_V

    std::array<glm::vec2, 6> output;

    // This is done since the side parts of the cube have the texture fliped
    // TODO: Possibly fix up the vertices to prevent this issue
    if (face == 2 || face == 3)
        output = {
            glm::vec2(rightX, topY),    // 1, 1
            glm::vec2(leftX,  topY),    // 0, 1
            glm::vec2(leftX,  bottomY), // 0, 0
            glm::vec2(leftX,  bottomY), // 0, 0
            glm::vec2(rightX, bottomY), // 1, 0
            glm::vec2(rightX, topY)     // 1, 1
        };
    
    else
        output = {
            glm::vec2(leftX,  bottomY),  // 0, 0
            glm::vec2(rightX, bottomY),  // 1, 0
            glm::vec2(rightX, topY),     // 1, 1
            glm::vec2(rightX, topY),     // 1, 1
            glm::vec2(leftX,  topY),     // 0, 1
            glm::vec2(leftX,  bottomY)   // 0, 0
        };
    

    return output;
}

} // namespace World::Block


#endif