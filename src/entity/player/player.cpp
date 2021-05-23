#include "player.hpp"

#include <iostream>

namespace Player
{

Player::Player(const glm::vec3 &startPos)
{
    position = startPos;
    //rotation.x = -90.0f;
}

void Player::handleInput(const sf::Window &window)
{
    keyboard();
    mouse(window);
}

void Player::update(float deltaTime)
{
    velocity.y = 0.0f;
    position += velocity * deltaTime;
    velocity.x *= 0.95f;
    velocity.z *= 0.95f;
}

void Player::keyboard()
{
    glm::vec3 change{0.0f};

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        change.x = glm::cos(glm::radians(rotation.x)) * speed;
        change.z = glm::sin(glm::radians(rotation.x)) * speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        change.x = -glm::cos(glm::radians(rotation.x)) * speed;
        change.z = -glm::sin(glm::radians(rotation.x)) * speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        change.x = -glm::cos(glm::radians(rotation.x + 90)) * speed;
        change.z = -glm::sin(glm::radians(rotation.x + 90)) * speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        change.x = glm::cos(glm::radians(rotation.x + 90)) * speed;
        change.z = glm::sin(glm::radians(rotation.x + 90)) * speed;
    }

    velocity += change;
    std::cout << velocity.x << ", " << velocity.y << ", " << velocity.z << '\n';
}

void Player::mouse(const sf::Window &window)
{
    const float BOUND = 89.0f;
    auto currentMousePos = sf::Mouse::getPosition(window);

    if (firstMouse)
    {
        lastX = currentMousePos.x;
        lastY = currentMousePos.y;
        firstMouse = false;
    }

    float xoffset = currentMousePos.x - lastX;
    float yoffset = lastY - currentMousePos.y;
    lastX = currentMousePos.x;
    lastY = currentMousePos.y;

    xoffset *= sensitivity;
    yoffset *= sensitivity;

    rotation.x += xoffset;
    rotation.y += yoffset;

    if (rotation.y > BOUND)
        rotation.y = BOUND;

    else if (rotation.y < -BOUND)
        rotation.y = -BOUND;
}

} // namespace Player
