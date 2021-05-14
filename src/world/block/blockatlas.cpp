#include "blockatlas.hpp"

namespace World::Block {

std::vector<float> GetTextureCoords(int column, int row) {
  const float maxColumn = 16.0f;
  const float maxRow = 16.0f;

  float leftX = column / maxColumn;               // left_U
  float rightX = (column + 1.0f) / maxColumn;     // right_U
  float topY = (maxRow - row) / maxRow;           // top_V
  float bottomY = (maxRow - row - 1.0f) / maxRow; // bottom_V

  return
  {
    leftX, bottomY,
    rightX, bottomY,
    rightX, topY,
    leftX, topY
  };
}

} // namespace World::Block
