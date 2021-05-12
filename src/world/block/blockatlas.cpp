#include "blockatlas.hpp"

namespace World::Block {

std::array<glm::vec2, 6> GetTextureCoords(int column, int row, int face) {
  const float maxColumn = 16.0f;
  const float maxRow = 16.0f;

  float leftX = column / maxColumn;               // left_U
  float rightX = (column + 1.0f) / maxColumn;     // right_U
  float topY = (maxRow - row) / maxRow;           // top_V
  float bottomY = (maxRow - row - 1.0f) / maxRow; // bottom_V

  std::array<glm::vec2, 6> output;

  switch (face) {
  case 0: // Back
    output = {
        glm::vec2(leftX, bottomY),  // 0, 0
        glm::vec2(rightX, topY),    // 1, 1
        glm::vec2(rightX, bottomY), // 1, 0
        glm::vec2(rightX, topY),    // 1, 1
        glm::vec2(leftX, bottomY),  // 0, 0
        glm::vec2(leftX, topY)      // 0, 1
    };
    break;

  case 1: // Front
    output = {
        glm::vec2(leftX, bottomY),  // 0, 0
        glm::vec2(rightX, bottomY), // 1, 0
        glm::vec2(rightX, topY),    // 1, 1
        glm::vec2(rightX, topY),    // 1, 1
        glm::vec2(leftX, topY),     // 0, 1
        glm::vec2(leftX, bottomY)   // 0, 0
    };
    break;

  case 2: // Left
    output = {
        glm::vec2(rightX, topY),    // 1, 1
        glm::vec2(leftX, topY),     // 0, 1
        glm::vec2(leftX, bottomY),  // 0, 0
        glm::vec2(leftX, bottomY),  // 0, 0
        glm::vec2(rightX, bottomY), // 1, 0
        glm::vec2(rightX, topY)     // 1, 1
    };
    break;

  case 3: // Right
    output = {
        glm::vec2(rightX, topY),   // 1, 1
        glm::vec2(leftX, bottomY), // 0, 0
        glm::vec2(leftX, topY),    // 0, 1
        glm::vec2(leftX, bottomY), // 0, 0
        glm::vec2(rightX, topY),   // 1, 1
        glm::vec2(rightX, bottomY) // 1, 0
    };
    break;

  case 4: // Bottom
    output = {
        glm::vec2(leftX, topY),     // 0, 1
        glm::vec2(rightX, topY),    // 1, 1
        glm::vec2(rightX, bottomY), // 1, 0
        glm::vec2(rightX, bottomY), // 1, 0
        glm::vec2(leftX, bottomY),  // 0, 0
        glm::vec2(leftX, topY)      // 0, 1
    };
    break;

  case 5: // Front
    output = {
        glm::vec2(leftX, topY),     // 0, 1
        glm::vec2(rightX, bottomY), // 1, 0
        glm::vec2(rightX, topY),    // 1, 1
        glm::vec2(rightX, bottomY), // 1, 0
        glm::vec2(leftX, topY),     // 0, 1
        glm::vec2(leftX, bottomY)   // 0, 0
    };
    break;

  default:
    break;
  }

  return output;
}

} // namespace World::Block
