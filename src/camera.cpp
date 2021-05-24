#include "camera.hpp"

#include "utils/constants.hpp"
#include "utils/maths.hpp"

Camera::Camera()
{
    float aspect = (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT;
    projectionMatrix = glm::perspective(3.14f / 2.0f, aspect, 0.1f, 1000.0f);
}

void Camera::update()
{
    // Update the camera's position and rotation to be linked to the entity's one
    position = ptEntity->position;
    rotation = ptEntity->rotation;

    viewMatrix = createViewMatrix(position, rotation);
}

void Camera::hookEntity(Entity &entity)
{
    ptEntity = &entity;
    update();
}

void Camera::unhookEntity()
{
    if (ptEntity)
    {
        ptEntity = nullptr;
    }
}

const glm::mat4& Camera::ViewMatrix() const
{
    return viewMatrix;
}

const glm::mat4& Camera::ProjMatrix() const
{
    return projectionMatrix;
}