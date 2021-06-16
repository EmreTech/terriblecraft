#ifndef PLAYING_STATE_HPP
#define PLAYING_STATE_HPP

#include "stateBase.hpp"
#include "../utils/glm_include.hpp"
#include "../renderer/renderMaster.hpp"
#include "../entity/player/player.hpp"
#include "../world/chunk/chunk_manager.hpp"
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
    Player::Player player{ { CHUNK_SIZE / 2, CHUNK_HEIGHT * 2 + 1, CHUNK_SIZE / 2 } };
    Camera *ptCamera = nullptr;

    bool wireframe = false;

    // Temporarily here for now
    World::ChunkManager test;
};

} // namespace States


#endif