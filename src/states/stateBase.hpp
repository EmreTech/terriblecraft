#ifndef STATE_BASE_HPP
#define STATE_BASE_HPP

#include <SFML/Graphics.hpp>

namespace States
{

struct BaseState
{
    virtual ~BaseState() = default;

    virtual void handleInput(sf::Keyboard::Key key) = 0;
    virtual void handleEvents(sf::Event event) = 0;

    virtual void update(float deltaTime) = 0;
    virtual void render() = 0;
};

} // namespace States


#endif