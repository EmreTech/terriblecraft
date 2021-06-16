#include "player.hpp"

#include <iostream>

#include "../../utils/maths.hpp"

namespace Player
{

Player::Player(const glm::vec3 &startPos)
{
    position   = startPos;
    rotation.x = 45.0f;
    velocity   = {0.0f, 0.0f, 0.0f};
}

void Player::handleInput(const sf::Window &window)
{
    keyboard();
    mouse(window);
}

void Player::update(float deltaTime)
{
    position += velocity * deltaTime;

    velocity.x *= 0.75f;
    velocity.y *= 0.75f;
    velocity.z *= 0.75f;
}

void Player::keyboard()
{
    float currentSpeed = speed;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
        currentSpeed *= 5.0f;

    glm::vec3 acceleration{0.0f};
    float &yaw = rotation.y;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        acceleration.x += glm::cos(glm::radians(yaw));
        acceleration.z += glm::sin(glm::radians(yaw));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        acceleration.x -= glm::cos(glm::radians(yaw));
        acceleration.z -= glm::sin(glm::radians(yaw));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        acceleration.x -= glm::cos(glm::radians(yaw + 90));
        acceleration.z -= glm::sin(glm::radians(yaw + 90));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        acceleration.x += glm::cos(glm::radians(yaw + 90));
        acceleration.z += glm::sin(glm::radians(yaw + 90));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        velocity.y += speed * 2.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        velocity.y -= speed * 2.0f;

    velocity += acceleration * currentSpeed;
}

void Player::mouse(const sf::Window &window)
{
    if (mouseMovements == 0)
    {
        // Fixes camera jittering on macOS (solution from open-builder)
#ifndef __APPLE__
        lastMousePosition = sf::Mouse::getPosition(window);
#else
        lastMousePosition.x = (int) window.getSize().x / 2;
        lastMousePosition.y = (int) window.getSize().y / 2;
#endif
        mouseMovements++;
    }

    auto mouseChange = sf::Mouse::getPosition(window) - lastMousePosition;

    float &yaw = rotation.y;
    float &pitch = rotation.x;

    yaw += static_cast<float>(mouseChange.x * sensitivity / 8.0f);
    pitch -= static_cast<float>(mouseChange.y * sensitivity / 8.0f);

    if (pitch > 89.0f)
        pitch = 89.0f;

    else if (pitch < -89.0f)
        pitch = -89.0f;

    if (yaw > 360.0f)
        yaw = 0.0f;

    else if (yaw < 0)
        yaw = 360.0f;

    auto cx = static_cast<int>(window.getSize().x) / 2;
    auto cy = static_cast<int>(window.getSize().y) / 2;
    sf::Mouse::setPosition({cx, cy}, window);

// Fixes camera jittering on macOS (solution from open-builder)
#ifndef __APPLE__
    lastMousePosition = sf::Mouse::getPosition(window);
#else
    lastMousePosition.x = (int) window.getSize().x / 2;
    lastMousePosition.y = (int) window.getSize().y / 2;
#endif

    if ((mouseChange.x < 0 || mouseChange.x > 0) ||
        (mouseChange.y < 0 || mouseChange.y > 0))
        mouseMovements++;
}

} // namespace Player
