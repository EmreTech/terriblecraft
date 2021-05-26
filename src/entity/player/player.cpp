#include "player.hpp"

#include <iostream>

#include "../../utils/maths.hpp"

namespace Player
{

Player::Player(const glm::vec3 &startPos)
{
    position = startPos;
    rotation.y = 90.0f;

    input.linkEntity(*this);
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

    position.y = 0.0f;

    std::cout << "Position: X: " << position.x << " Y: " << position.y << " Z: " << position.z << '\n';
}

void Player::keyboard()
{
    /*
    float yaw90 = glm::radians(rotation.y + 90);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        acceleration.x += -glm::cos(yaw90) * speed;
        acceleration.z += -glm::sin(yaw90) * speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        acceleration.x += glm::cos(yaw90) * speed;
        acceleration.z += glm::sin(yaw90) * speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        acceleration += leftVector(rotation) * speed;

        // This is to ensure the acceleration vector is actually going left
 
        acceleration.x += -glm::cos(yaw90) * speed;
        acceleration.z += -glm::sin(yaw90) * speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        acceleration += rightVector(rotation) * speed;

        // This is to ensure the acceleration vector is actually going right

        acceleration.x += glm::cos(yaw90) * speed;
        acceleration.z += glm::sin(yaw90) * speed;
    }
    */

    float currentSpeed = speed;

    PlayerMovement movement;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
            currentSpeed *= 10.0f;

        movement = PlayerMovement::FORWARD;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        movement = PlayerMovement::BACKWARD;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        movement = PlayerMovement::LEFT;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        movement = PlayerMovement::RIGHT;

    input.keyboardInput(movement, currentSpeed);
}

void Player::mouse(const sf::Window &window)
{
    auto mouseChange = sf::Mouse::getPosition(window) - lastMousePosition;

    input.mouseInput(mouseChange, sensitivity);

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
