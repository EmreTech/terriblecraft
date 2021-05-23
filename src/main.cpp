#include <memory>
#include <vector>

#include "window.hpp"
#include "camera.hpp"
#include "states/playingState.hpp"
#include "utils/clock.hpp"
#include "renderer/renderMaster.hpp"

float r = 12.0f;
float g = 155.0f;
float b = 175.0f;

std::vector<std::unique_ptr<States::BaseState>> states;
Window window;
Camera cam;

void handleEvents(bool &running)
{
    sf::Event event;
    while (window.getWindow().pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
            running = false;
            break;
    
            case sf::Event::Resized:
            glViewport(0, 0, event.size.width, event.size.height);
            break;

            case sf::Event::KeyPressed:
            switch (event.key.code)
            {
                case sf::Keyboard::Escape:
                running = false;
                break;

                default:
                break;
            }
            break;

            default:
            break;
        }
    }
}

int main()
{
    window.create();
    window.getWindow().setActive();

    Renderer::RenderMaster master;
    
    states.push_back(std::make_unique<States::PlayingState>(cam, window));

    Clock delta;
    float deltaTime = 0.0f, lastFrame = 0.0f;

    bool running = true;
    while (running)
    {
        // Calculate delta time

        float currentTime = delta.elapsed();
        deltaTime = currentTime - lastFrame;
        lastFrame = currentTime;

        auto &currentState = *states.back();

        // Update

        currentState.handleInput();
        currentState.update(deltaTime);
        cam.update();

        // Render

        currentState.render(master);
        glClearColor(r / 255, g / 255, b / 255, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // BUG: Camera approach is somehow not rendering the quad?
        master.finishRender(cam);

        window.getWindow().display();

        // Handle events

        handleEvents(running);
    }

    return EXIT_SUCCESS;
}