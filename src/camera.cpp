#include "camera.hpp"

#include "utils/constants.hpp"

Camera::Camera()
{
    setProjType(ProjectionType::PERSPECTIVE);
    position = {0.0f, 0.0f, 0.0f};
}

void Camera::setProjType(const ProjectionType &newType)
{
    type = newType;

    switch (type)
    {
        case ProjectionType::PERSPECTIVE:
        projectionMatrix = glm::perspective(glm::radians(90.0f), (float) (WINDOW_WIDTH / WINDOW_HEIGHT), 0.1f, 1000.0f);
        break;

        case ProjectionType::ORTHOGRAPHIC:
        projectionMatrix = glm::ortho(0.0f, (float) WINDOW_WIDTH, 0.0f, (float) WINDOW_HEIGHT, 0.1f, 1000.0f);
        break;
    }
}

void Camera::makeViewMatrix()
{
    viewMatrix = glm::rotate(viewMatrix, glm::radians(rotation.x), {1, 0, 0});
    viewMatrix = glm::rotate(viewMatrix, glm::radians(rotation.y), {0, 1, 0});
    viewMatrix = glm::rotate(viewMatrix, glm::radians(rotation.z), {0, 0, 1});
    viewMatrix = glm::translate(viewMatrix, position);
}

void Camera::update()
{
    position = ptEntity->position;
    rotation = ptEntity->rotation;

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