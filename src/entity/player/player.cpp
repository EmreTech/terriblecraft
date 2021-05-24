#include "player.hpp"

#include <iostream>

#include "../../utils/maths.hpp"

namespace Player
{

Player::Player(const glm::vec3 &startPos)
{
    position = startPos;
    rotation.y = 90.0f;
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
    velocity.z *= 0.75f;

    //position.z = 0.0f;
    //std::cout << "Position: X: " << position.x << " Y: " << position.y << " Z: " << position.z << '\n';
    //std::cout << "Yaw: " << rotation.y << " Pitch: " << rotation.x << '\n';
}

void Player::keyboard()
{
    glm::vec3 change{0.0f};

    float yaw = glm::radians(rotation.y);
    float yaw90 = glm::radians(rotation.y + 90);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        change.x -= glm::cos(yaw90) * speed;
        change.z -= glm::sin(yaw90) * speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        change.x += glm::cos(yaw90) * speed;
        change.z += glm::sin(yaw90) * speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        change.x -= glm::cos(yaw) * speed;
        change.z -= glm::sin(yaw) * speed;

        // This is to ensure the change vector is actually going left

        change.x -= glm::cos(yaw90) * speed;
        change.z -= glm::sin(yaw90) * speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        change.x += glm::cos(yaw) * speed;
        change.z += glm::sin(yaw) * speed;

        // This is to ensure the change vector is actually going right

        change.x += glm::cos(yaw90) * speed;
        change.z += glm::sin(yaw90) * speed;
    }

    velocity += change;

    if (rotation.x > 85.0f)
    {
        rotation.x = 84.9f;
    }
    else if (rotation.x < -80.0f)
    {
        rotation.x = -79.9f;
    }
}

void Player::mouse(const sf::Window &window)
{
    auto mouseChange = sf::Mouse::getPosition(window) - lastMousePosition;

    rotation.x += static_cast<float>(mouseChange.y / 8.0f * sensitivity); // Pitch
    rotation.y += static_cast<float>(mouseChange.x / 8.0f * sensitivity); // Yaw

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
}

} // namespace Player
