#include <memory>
#include <vector>

#include "window.hpp"
#include "states/playingState.hpp"

float r = 12.0f;
float g = 155.0f;
float b = 175.0f;

std::vector<std::unique_ptr<States::BaseState>> states;
Window window;

void handleEvents(bool &running, States::BaseState &currentState)
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
    
            default:
            break;
        }

        currentState.handleEvents(event);
    }
}

int main()
{
    window.create();
    window.getWindow().setVerticalSyncEnabled(true);
    
    states.push_back(std::make_unique<States::PlayingState>());

    bool running = true;
    while (running)
    {
        auto &currentState = *states.back();

        handleEvents(running, currentState);
        currentState.update(0.0f);

        glClearColor(r / 255, g / 255, b / 255, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        currentState.render();

        window.getWindow().display();
    }

    return EXIT_SUCCESS;
}