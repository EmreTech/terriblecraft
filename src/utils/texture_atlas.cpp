#include "texture_atlas.hpp"

std::array<float, 8> GetTextureCoords(int column, int row, float maxColumn, float maxRow) 
{
    float leftX = column / maxColumn;            
    float rightX = (column + 1.0f) / maxColumn;    
    float topY = (row + 1.0f) / maxRow;          
    float bottomY = row / maxRow;

    return
    {
        leftX, bottomY,
        rightX, bottomY,
        rightX, topY,
        leftX, topY,
    };
}

std::array<float, 8> GetTextureCoords(sf::Vector2i coords, float maxColumn, float maxRow)
{
    return GetTextureCoords(coords.x, coords.y, maxColumn, maxRow);
}