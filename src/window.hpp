#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <glad/glad.h>
#include <SFML/Window.hpp>

#include <iostream>

#include "utils/constants.hpp"

struct Window
{
    Window() = default;

    void create();
    sf::Window& getWindow();

    private:
    sf::Window window;
};

#endif