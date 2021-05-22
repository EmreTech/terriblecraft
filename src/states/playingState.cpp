#include "playingState.hpp"

namespace States
{

PlayingState::PlayingState() {}

void PlayingState::handleInput(sf::Keyboard::Key key)
{}

void PlayingState::handleEvents(sf::Event event)
{}

void PlayingState::update(float deltaTime)
{}

void PlayingState::render()
{
    renderer.render();
}

} // namespace States
