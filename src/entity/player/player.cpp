#include "player.hpp"

#include <iostream>

#include "../../utils/maths.hpp"

namespace Player
{

Player::Player(const glm::vec3 &startPos)
{
    position   = startPos;
    velocity   = {0.0f, 0.0f, 0.0f};

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
    velocity.y *= 0.75f;
    velocity.z *= 0.75f;
}

void Player::keyboard()
{
    float currentSpeed = speed;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
        currentSpeed *= 20.0f;

    PlayerMovement movement;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        movement = PlayerMovement::FORWARD;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        movement = PlayerMovement::BACKWARD;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        movement = PlayerMovement::LEFT;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        movement = PlayerMovement::RIGHT;

    input.keyboardInput(movement, currentSpeed);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        velocity.y += currentSpeed;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        velocity.y -= currentSpeed;
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
