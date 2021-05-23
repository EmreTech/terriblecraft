#include "player.hpp"

#include <iostream>

namespace Player
{

Player::Player(const glm::vec3 &startPos)
{
    position = startPos;
}

void Player::handleInput(const sf::Window &window)
{
    keyboard();
    mouse(window);
}

void Player::update(float deltaTime)
{
    position += velocity * deltaTime;
    velocity *= 0.95f;
}

void Player::keyboard()
{
    glm::vec3 change;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        change.x = glm::cos(glm::radians(rotation.y + 90)) * speed;
        change.z = glm::sin(glm::radians(rotation.y + 90)) * speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        change.x = -glm::cos(glm::radians(rotation.y + 90)) * speed;
        change.z = -glm::sin(glm::radians(rotation.y + 90)) * speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        change.x = glm::cos(glm::radians(rotation.y)) * speed;
        change.z = glm::sin(glm::radians(rotation.y)) * speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        change.x = -glm::cos(glm::radians(rotation.y)) * speed;
        change.z = -glm::sin(glm::radians(rotation.y)) * speed;
    }

    velocity += change;
}

void Player::mouse(const sf::Window &window)
{
    const float BOUND = 80.0f;
    static auto lastMousePos = sf::Mouse::getPosition(window);
    auto difference = sf::Mouse::getPosition() - lastMousePos;

    rotation.y += difference.x * sensitivity;
    rotation.x += difference.y * sensitivity;

    if (rotation.x > BOUND)
        rotation.x = BOUND;

    else if (rotation.x < -BOUND)
        rotation.x = -BOUND;

    if (rotation.y > 360.0f)
        rotation.y = 0;

    else if (rotation.y < 0)
        rotation.y = 360;

    //auto newX = static_cast<int>(window.getSize().x / 2);
    //auto newY = static_cast<int>(window.getSize().y / 2);
    //sf::Mouse::setPosition({newX, newY}, window);

    lastMousePos = sf::Mouse::getPosition();
}

} // namespace Player
