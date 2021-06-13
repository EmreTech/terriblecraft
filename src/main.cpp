#include <memory>
#include <vector>

#include "window.hpp"
#include "camera.hpp"
#include "states/playingState.hpp"
#include "utils/clock.hpp"
#include "renderer/renderMaster.hpp"

// Colors
float r = 63.75f;
float g = 191.25f;
float b = 255.0f;

std::vector<std::unique_ptr<States::BaseState>> states;
Camera cam;

// Timing
float deltaTime = 0.0f, lastFrame = 0.0f;

void handleEvents(bool &running, States::BaseState &currentState)
{
    sf::Event event;
    while (Window::get().pollEvent(event))
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
        currentState.handleEvents(event);
    }
}

void update(States::BaseState &currentState)
{
    currentState.handleInput();
    currentState.update(deltaTime);
    cam.update();
}

void render(States::BaseState &currentState, Renderer::RenderMaster &master)
{
    currentState.render(master);
    glClearColor(r / 255, g / 255, b / 255, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    master.finishRender(cam);

    Window::get().display(); 
}

int main()
{
    Window::create();

    Renderer::RenderMaster master;
    
    states.push_back(std::make_unique<States::PlayingState>(cam));

    Clock delta;
    bool running = true;

    while (running)
    {
        // Calculate delta time
        float currentTime = delta.elapsed();
        deltaTime = currentTime - lastFrame;
        lastFrame = currentTime;

        auto &currentState = *states.back();

        update(currentState);
        render(currentState, master);

        handleEvents(running, currentState);
    }

    return EXIT_SUCCESS;
}