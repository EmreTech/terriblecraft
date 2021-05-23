#include "window.hpp"

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


void Window::create()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;
    settings.majorVersion = 3;
    settings.minorVersion = 3;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.attributeFlags = sf::ContextSettings::Core;

    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "TerribleCraft", sf::Style::Default, settings);
    window.setPosition({window.getPosition().x, 0});

    if (!loadGL())
        exit(1);
}

sf::Window& Window::getWindow()
{
    return window;
}