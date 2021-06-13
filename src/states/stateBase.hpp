#ifndef STATE_BASE_HPP
#define STATE_BASE_HPP

#include <SFML/Window/Event.hpp>

#include "../camera.hpp"

namespace Renderer
{

struct RenderMaster;

} // namespace Renderer

namespace States
{

struct BaseState
{
    virtual ~BaseState() = default;

    virtual void handleInput() = 0;
    virtual void handleEvents(sf::Event event) = 0;

    virtual void update(float deltaTime) = 0;
    virtual void render(Renderer::RenderMaster &renderer) = 0;
};

} // namespace States


#endif