#ifndef PLAYER_INPUT_HPP
#define PLAYER_INPUT_HPP

#include <SFML/System/Vector2.hpp>

#include "../../utils/glm_include.hpp"
#include "../entity.hpp"

struct Camera;

namespace Player
{

enum class PlayerMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
};

struct PlayerInput
{
    PlayerInput() = default;
    PlayerInput(Entity &entity);
    ~PlayerInput();

    void linkEntity(Entity &entity);
    void unlinkEntity();

    void keyboardInput(PlayerMovement movement, float speed);
    void mouseInput(sf::Vector2i change, float sensitivity);

    private:
    Entity *ptEntity = nullptr;
};

} // namespace Player


#endif