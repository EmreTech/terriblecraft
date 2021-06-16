#include "playingState.hpp"

#include "../world/chunk/chunk_mesh_builder.hpp"
#include "../world/block/block_data.hpp"
#include "../world/world_constants.hpp"
#include "../world/coordinate.hpp"
#include "../camera.hpp"

namespace States
{

PlayingState::PlayingState(Camera &cam) : ptCamera(&cam)
{
    ptCamera->hookEntity(player);
    auto &chunk = test.addChunk({0, 0, 0});

    for (int y = 0; y < CHUNK_HEIGHT; y++)
    for (int x = 0; x < CHUNK_SIZE; x++)
    for (int z = 0; z < CHUNK_SIZE; z++)
    {
        chunk.quickSetBlock({x, y, z}, World::BlockDataManager::get().getId("grass"));
    }
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

    renderer.drawChunk(test.getChunk({0, 0, 0}));
}

} // namespace States
