#ifndef MATHS_HPP
#define MATHS_HPP

#include "glm_include.hpp"

struct Camera;

void rotateMatrix(glm::mat4 &matrix, const glm::vec3 &degrees);
void translateMatrix(glm::mat4 &matrix, const glm::vec3 &offset);

glm::mat4 createViewMatrix(Camera &camera);
glm::mat4 createProjectionMatrix(Camera &camera);

glm::vec3 forwardsVector(const glm::vec3 &rotation);
glm::vec3 backwardsVector(const glm::vec3 &rotation);
glm::vec3 leftVector(const glm::vec3& rotation);
glm::vec3 rightVector(const glm::vec3 &rotation);

#endif