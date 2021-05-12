#ifndef BLOCKATLAS_HPP
#define BLOCKATLAS_HPP

#include <glm/vec2.hpp>

#include <array>

namespace World::Block {

std::array<glm::vec2, 6> GetTextureCoords(int column, int row, int face);

} // namespace World::Block

#endif