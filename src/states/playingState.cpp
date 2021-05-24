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
    glm::vec3 camPos;
    //camPos = ptCamera->position;
    camPos.z += 2.0f;
    renderer.drawQuad(camPos);

    camPos.x += 2.0f;
    renderer.drawQuad(camPos);

    camPos.x -= 4.0f;
    renderer.drawQuad(camPos);
}

} // namespace States
