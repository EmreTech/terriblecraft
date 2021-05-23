#include "camera.hpp"

#include "utils/constants.hpp"

Camera::Camera()
{
    projectionMatrix = glm::perspective(glm::radians(90.0f), (float) (WINDOW_WIDTH / WINDOW_HEIGHT), 0.1f, 1000.0f);
    position = {0.0f, 0.0f, 0.0f};
}

void Camera::makeViewMatrix()
{
    viewMatrix = glm::lookAt(position, position + Front, Up);
}

void Camera::update()
{
    // Update the camera's position and rotation to be linked to the entity's one
    position = ptEntity->position;
    rotation = ptEntity->rotation;

    // Recalculate the vectors every time we move
    glm::vec3 front;
    front.x = cos(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));
    front.y = sin(glm::radians(rotation.y));
    front.z = sin(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));
    Front = glm::normalize(front);
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));

    makeViewMatrix();
}

void Camera::hookEntity(Entity &entity)
{
    ptEntity = &entity;
}

void Camera::unhookEntity()
{
    if (ptEntity)
        ptEntity = nullptr;
}

const glm::mat4& Camera::ViewMatrix() const
{
    return viewMatrix;
}

const glm::mat4& Camera::ProjMatrix() const
{
    return projectionMatrix;
}