#include "playerInput.hpp"

#include "../../camera.hpp"

namespace Player
{

PlayerInput::PlayerInput(Entity &entity)
{
    linkEntity(entity);
}

PlayerInput::~PlayerInput()
{
    unlinkEntity();
}

void PlayerInput::linkEntity(Entity &entity)
{
    ptEntity = &entity;
}

void PlayerInput::unlinkEntity()
{
    if (ptEntity)
    {
        ptEntity = nullptr;
    }
}

void PlayerInput::keyboardInput(PlayerMovement movement, float speed)
{
    if (!ptEntity)
        return;

    if (!ptEntity->ptCamera)
        return;

    float yaw = ptEntity->rotation.y;

    Camera &cam = *(ptEntity->ptCamera);
    glm::vec3 acceleration{0.0f};

    switch (movement)
    {
        case PlayerMovement::FORWARD:
        acceleration.x += glm::cos(glm::radians(yaw));
        acceleration.z += glm::sin(glm::radians(yaw));
        break;

        case PlayerMovement::BACKWARD:
        acceleration.x -= glm::cos(glm::radians(yaw));
        acceleration.z -= glm::sin(glm::radians(yaw));
        break;

        case PlayerMovement::LEFT:
        acceleration -= cam.Right;
        break;

        case PlayerMovement::RIGHT:
        acceleration += cam.Right;
        break;
    }

    acceleration * speed;
    ptEntity->velocity += acceleration;
}

void PlayerInput::mouseInput(sf::Vector2i change, float sensitivity)
{
    if (!ptEntity)
        return;

    float &yaw = ptEntity->rotation.y;
    float &pitch = ptEntity->rotation.x;

    yaw += static_cast<float>(change.x * sensitivity / 8.0f);
    pitch -= static_cast<float>(change.y * sensitivity / 8.0f);

    if (pitch > 89.0f)
        pitch = 89.0f;

    else if (pitch < -89.0f)
        pitch = -89.0f;
}

} // namespace Player
