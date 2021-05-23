#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Window.hpp>

#include "../entity.hpp"

namespace Player
{

struct Player : public Entity
{
    Player(const glm::vec3 &startPos);

    void handleInput(const sf::Window &window);
    void update(float deltaTime);

    private:
    void keyboard();
    void mouse(const sf::Window &window);

    glm::vec3 velocity;
    const float speed = 0.5f;
    const float sensitivity = 0.05f;
};

} // namespace Player


#endif