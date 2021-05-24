#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <glad/glad.h>
#include <SFML/Window.hpp>

#include <iostream>

#include "utils/constants.hpp"

namespace Window
{

void create();
sf::Window &get();

} // namespace Window


#endif