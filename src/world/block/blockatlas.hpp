#ifndef BLOCKATLAS_HPP
#define BLOCKATLAS_HPP

#include <vector>

#include "../../utils/glm_include.hpp"

namespace World::Block {

std::vector<float> GetTextureCoords(int column, int row);

} // namespace World::Block

#endif