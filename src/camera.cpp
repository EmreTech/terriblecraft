#include "camera.hpp"

#include "utils/maths.hpp"
#include "window.hpp"

Camera::Camera()
{
    Up = glm::vec3(0.0f, 1.0f, 0.0f);
    Front = glm::vec3(0.0f, 0.0f, -1.0f);
    WorldUp = Up;
    updateVectors();

    float aspect = (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT;
    projectionMatrix = glm::perspective(3.14f / 4.0f, aspect, 0.01f, 1000.0f);
}

Camera::~Camera()
{
    unhookEntity();
}

void Camera::update()
{
    // Update the camera's position and rotation to be linked to the entity's one
    position = ptEntity->position;
    rotation = ptEntity->rotation;

    updateVectors();
    viewMatrix = createViewMatrix(*this);
}

void Camera::hookEntity(Entity &entity)
{
    ptEntity = &entity;
    ptEntity->ptCamera = this;
    update();
}

void Camera::unhookEntity()
{
    if (ptEntity)
    {
        ptEntity->ptCamera = nullptr;
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

void Camera::updateVectors()
{
    float yaw = rotation.y;
    float pitch = rotation.x;

    glm::vec3 tmpFront;
    tmpFront.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
    tmpFront.y = glm::sin(glm::radians(pitch));
    tmpFront.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
    Front = glm::normalize(tmpFront);

    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}