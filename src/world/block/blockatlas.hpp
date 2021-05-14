#ifndef BLOCKATLAS_HPP
#define BLOCKATLAS_HPP

#include <glm/vec2.hpp>

#include <vector>

namespace World::Block {

std::vector<float> GetTextureCoords(int column, int row);

} // namespace World::Block

#endif