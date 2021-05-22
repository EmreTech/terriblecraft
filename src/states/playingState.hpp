#ifndef PLAYING_STATE_HPP
#define PLAYING_STATE_HPP

#include "stateBase.hpp"
#include "../renderer/quadRenderer.hpp"

namespace States
{

struct PlayingState : public BaseState
{
    PlayingState();

    void handleInput(sf::Keyboard::Key key) override;
    void handleEvents(sf::Event event) override;

    void update(float deltaTime) override;
    void render() override;

    private:
    Renderer::QuadRenderer renderer;
};

} // namespace States


#endif