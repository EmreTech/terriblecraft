#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Window.hpp>

#include "../entity.hpp"
#include "../../utils/constants.hpp"
#include "../../camera.hpp"
#include "playerInput.hpp"

namespace Player
{

struct PlayerInput;

struct Player : public Entity
{
    Player(const glm::vec3 &startPos);

    void handleInput(const sf::Window &window);
    void update(float deltaTime);

    private:
    const float speed = 0.5f;
    const float sensitivity = 1.f;

    void keyboard();
    void mouse(const sf::Window &window);

    PlayerInput input;

    sf::Vector2i lastMousePosition;
};

} // namespace Player


#endif