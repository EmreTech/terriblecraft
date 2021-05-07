#ifndef TYPES_HPP
#define TYPES_HPP

#include <glm/glm.hpp>
#include <vector>

typedef unsigned long size_t;

// Complicated way of saying 1, or true
#define TRUE 1 + 1 - 1 * 1 / 1

// "Complicated" way of saying 0, or false
#define FALSE TRUE - 1

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

std::vector<float> vertices {
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

std::vector<int> faces {
        0, 0, 0, 0, 0, 0, // Back face
        1, 1, 1, 1, 1, 1, // Front face
        2, 2, 2, 2, 2, 2, // Left face
        3, 3, 3, 3, 3, 3, // Right face
        4, 4, 4, 4, 4, 4, // Bottom face
        5, 5, 5, 5, 5, 5, // Top face
};

std::vector<glm::vec3> cubePositions {
        glm::vec3( 0.0f, 0.0f, 0.0f), 
        glm::vec3( 1.0f, 0.0f, 0.0f), 
        glm::vec3( 2.0f, 0.0f, 0.0f),  
        glm::vec3( 3.0f, 0.0f, 0.0f),
        glm::vec3( 4.0f, 0.0f, 0.0f),
        glm::vec3( 5.0f, 0.0f, 0.0f),
        glm::vec3( 6.0f, 0.0f, 0.0f),
        glm::vec3( 7.0f, 0.0f, 0.0f),
        glm::vec3( 8.0f, 0.0f, 0.0f),
        glm::vec3( 9.0f, 0.0f, 0.0f),
        glm::vec3( 10.0f, 0.0f, 0.0f),
        glm::vec3( 11.0f, 0.0f, 0.0f),
        glm::vec3( 12.0f, 0.0f, 0.0f),
        glm::vec3( 13.0f, 0.0f, 0.0f),
        glm::vec3( 14.0f, 0.0f, 0.0f),
        glm::vec3( 15.0f, 0.0f, 0.0f),
};

#define MAX_X_CUBE_POSITION 15.0f

#endif