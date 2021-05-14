#ifndef MESH_HPP
#define MESH_HPP

#include <vector>

struct Mesh {
  std::vector<float> vertexPositions;
  std::vector<float> textureCoords;
  std::vector<unsigned int> indices;
};

#endif