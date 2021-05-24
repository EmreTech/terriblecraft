#include "window.hpp"

#include <memory>

namespace
{

bool loadGL()
{
    if (!gladLoadGL())
    {
        std::cerr << "Error: Failed when attemping to load Glad" << '\n';
        return false;
    }

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glEnable(GL_DEPTH_TEST);

    return true;
}

} // namespace

namespace Window
{

std::unique_ptr<sf::Window> window_ptr;

void create()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;
    settings.majorVersion = 3;
    settings.minorVersion = 3;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.attributeFlags = sf::ContextSettings::Core;

    window_ptr = std::make_unique<sf::Window>(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), 
                                              "TerribleCraft", 
                                              sf::Style::Close, 
                                              settings);
    window_ptr->setKeyRepeatEnabled(false);
    window_ptr->setMouseCursorVisible(false);

    if (!loadGL())
        exit(1);
}

sf::Window& get()
{
    return *window_ptr;
}



} // namespace Window
