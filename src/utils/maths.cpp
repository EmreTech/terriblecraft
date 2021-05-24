#include "maths.hpp"

glm::mat4 createViewMatrix(const glm::vec3 &position, const glm::vec3 &rotation)
{
    glm::mat4 view{1.0f};

    rotateMatrix(view, rotation);
    translateMatrix(view, -position);

    return view;
}

void rotateMatrix(glm::mat4 &matrix, const glm::vec3 &degrees)
{
    matrix = glm::rotate(matrix, glm::radians(degrees.x), {1, 0, 0});
    matrix = glm::rotate(matrix, glm::radians(degrees.y), {0, 1, 0});
    matrix = glm::rotate(matrix, glm::radians(degrees.z), {0, 0, 1});
}

void translateMatrix(glm::mat4 &matrix, const glm::vec3 &offset)
{
    matrix = glm::translate(matrix, offset);
}

glm::vec3 forwardsVector(const glm::vec3 &rotation)
{
    float yaw = glm::radians(rotation.y + 90);
    float pitch = glm::radians(rotation.x);

    float x = glm::cos(yaw) * glm::cos(pitch);
    float y = glm::sin(pitch);
    float z = glm::cos(pitch) * glm::sin(yaw);

    return {-x, -y, -z};
}

glm::vec3 backwardsVector(const glm::vec3 &rotation)
{
    return -forwardsVector(rotation);
}

glm::vec3 leftVector(const glm::vec3& rotation)
{
    float yaw = glm::radians(rotation.y);

    float x = glm::cos(yaw);
    float y = 0;
    float z = glm::sin(yaw);

    return {-x, -y, -z};
}

glm::vec3 rightVector(const glm::vec3 &rotation)
{
    return -leftVector(rotation);
}