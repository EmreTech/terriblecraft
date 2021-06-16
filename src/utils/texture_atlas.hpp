#ifndef TEXTURE_ATLAS_HPP
#define TEXTURE_ATLAS_HPP

#include <SFML/System/Vector2.hpp>

#include <array>

std::array<float, 8> GetTextureCoords(int column, int row, float maxColumn, float maxRow);
std::array<float, 8> GetTextureCoords(sf::Vector2i coords, float maxColumn, float maxRow);

#endif