#include "playingState.hpp"

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
{}

void PlayingState::update(float deltaTime)
{
    player.update(deltaTime);
}

void PlayingState::render(Renderer::RenderMaster &renderer)
{
    renderer.drawCube({0.0f, -0.5f, 3.0f});
}

} // namespace States
