#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Window.hpp>

#include "../entity.hpp"
#include "../../utils/constants.hpp"
#include "../../camera.hpp"

namespace Player
{

struct Player : public Entity
{
    Player(const glm::vec3 &startPos);

    void handleInput(const sf::Window &window);
    void update(float deltaTime);

    private:
    const float speed = 0.5f;
    const float sensitivity = 0.1f;

    void keyboard();
    void mouse(const sf::Window &window);

    glm::vec3 velocity;

    sf::Vector2i lastMousePosition;
};

} // namespace Player


#endif