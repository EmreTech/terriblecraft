#ifndef PLAYING_STATE_HPP
#define PLAYING_STATE_HPP

#include "stateBase.hpp"
#include "../utils/glm_include.hpp"
#include "../renderer/renderMaster.hpp"
#include "../entity/player/player.hpp"
#include "../window.hpp"

namespace States
{

struct PlayingState : public BaseState
{
    PlayingState(Camera &cam);

    void handleInput() override;
    void handleEvents(sf::Event event) override;

    void update(float deltaTime) override;
    void render(Renderer::RenderMaster &renderer) override;

    private:
    Player::Player player{ {0.0f, 0.0f, 0.0f} };
    Camera *ptCamera = nullptr;
};

} // namespace States


#endif