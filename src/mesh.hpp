#ifndef MESH_HPP
#define MESH_HPP

#include <vector>

/*
Gone for now, will be restored
std::vector<float> BaseVertices {
     // Back face
    -0.5f, -0.5f, -0.5f, // Bottom-left
     0.5f,  0.5f, -0.5f, // top-right
     0.5f, -0.5f, -0.5f, // bottom-right
     0.5f,  0.5f, -0.5f, // top-right
    -0.5f, -0.5f, -0.5f, // bottom-left
    -0.5f,  0.5f, -0.5f, // top-left
    // Front face
    -0.5f, -0.5f,  0.5f, // bottom-left
     0.5f, -0.5f,  0.5f, // bottom-right
     0.5f,  0.5f,  0.5f, // top-right
     0.5f,  0.5f,  0.5f, // top-right
    -0.5f,  0.5f,  0.5f, // top-left
    -0.5f, -0.5f,  0.5f, // bottom-left
    // Left face
    -0.5f,  0.5f,  0.5f, // top-right
    -0.5f,  0.5f, -0.5f, // top-left
    -0.5f, -0.5f, -0.5f, // bottom-left
    -0.5f, -0.5f, -0.5f, // bottom-left
    -0.5f, -0.5f,  0.5f, // bottom-right
    -0.5f,  0.5f,  0.5f, // top-right
    // Right face
     0.5f,  0.5f,  0.5f, // top-left
     0.5f, -0.5f, -0.5f, // bottom-right
     0.5f,  0.5f, -0.5f, // top-right
     0.5f, -0.5f, -0.5f, // bottom-right
     0.5f,  0.5f,  0.5f, // top-left
     0.5f, -0.5f,  0.5f, // bottom-left
    // Bottom face
    -0.5f, -0.5f, -0.5f, // top-right
     0.5f, -0.5f, -0.5f, // top-left
     0.5f, -0.5f,  0.5f, // bottom-left
     0.5f, -0.5f,  0.5f, // bottom-left
    -0.5f, -0.5f,  0.5f, // bottom-right
    -0.5f, -0.5f, -0.5f, // top-right
    // Top face
    -0.5f,  0.5f, -0.5f, // top-left
     0.5f,  0.5f,  0.5f, // bottom-right
     0.5f,  0.5f, -0.5f, // top-right
     0.5f,  0.5f,  0.5f, // bottom-right
    -0.5f,  0.5f, -0.5f, // top-left
    -0.5f,  0.5f,  0.5f, // bottom-left
};
*/

struct Mesh {
  std::vector<float> vertexPositions;
  std::vector<float> textureCoords;
  const std::vector<int> faces{
      0, 0, 0, 0, 0, 0, // Back face
      1, 1, 1, 1, 1, 1, // Front face
      2, 2, 2, 2, 2, 2, // Left face
      3, 3, 3, 3, 3, 3, // Right face
      4, 4, 4, 4, 4, 4, // Bottom face
      5, 5, 5, 5, 5, 5, // Top face
  };
};

#endif