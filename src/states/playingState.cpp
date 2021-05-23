#include "playingState.hpp"

#include "../camera.hpp"

namespace States
{

PlayingState::PlayingState(Camera &cam, Window &window) : ptWindow(&window)
{
    cam.hookEntity(player);
}

void PlayingState::handleInput()
{
    player.handleInput(ptWindow->getWindow());
}

void PlayingState::handleEvents(sf::Event event)
{}

void PlayingState::update(float deltaTime)
{
    player.update(deltaTime);
}

void PlayingState::render(Renderer::RenderMaster &renderer)
{
    renderer.drawQuad({0.0f, 0.0f, 2.0f});
}

} // namespace States
