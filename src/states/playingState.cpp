#include "playingState.hpp"

#include "../world/world_constants.hpp"
#include "../world/coordinate.hpp"
#include "../camera.hpp"

namespace States
{

PlayingState::PlayingState(Camera &cam) : ptCamera(&cam)
{
    ptCamera->hookEntity(player);
}

void PlayingState::handleInput()
{
    player.handleInput(Window::get());
}

void PlayingState::handleEvents(sf::Event event)
{
    switch (event.type)
    {
        case sf::Event::KeyPressed:
        switch (event.key.code)
        {
            case sf::Keyboard::V:
            wireframe = !wireframe;
            break;

            default:
            break;
        }
        break;

        default:
        break;
    }
}

void PlayingState::update(float deltaTime)
{
    player.update(deltaTime);
}

void PlayingState::render(Renderer::RenderMaster &renderer)
{
    glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
    
    renderer.drawCube({0.0f, 0.0f, 3.0f});
}

} // namespace States
