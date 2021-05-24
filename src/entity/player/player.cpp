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
    std::cout << "Position: X: " << position.x << " Y: " << position.y << " Z: " << position.z << '\n';
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
}

void Player::mouse(const sf::Window &window)
{
    // TODO: Ensure the mouse movement doesn't have any weird effects

    const float BOUND = 89.0f;
    auto mouseChange = sf::Mouse::getPosition(window) - lastMousePosition;

    rotation.x += mouseChange.y * sensitivity;
    rotation.y += mouseChange.x * sensitivity;

    if (rotation.x > BOUND)
    {
        rotation.x = BOUND;
    }
    else if (rotation.x < -BOUND)
    {
        rotation.x = -BOUND;
    }

    if (rotation.y < 0)
    {
        rotation.y = 360;
    }
    else if (rotation.y > 360)
    {
        rotation.y = 0;
    }

    //auto cx = static_cast<int>(window.getSize().x) / 4;
    //auto cy = static_cast<int>(window.getSize().y) / 4;
    //sf::Mouse::setPosition({cx, cy}, window);

    lastMousePosition = sf::Mouse::getPosition(window);
}

} // namespace Player
