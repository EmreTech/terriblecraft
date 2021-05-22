#include "keyboard.hpp"

namespace Input
{

Keyboard& Keyboard::getInstance()
{
    static Keyboard k;
    return k;
}

bool Keyboard::getPressedKey(int key)
{
    if (pressedKeys.find(key) == pressedKeys.end())
        return false;

    return pressedKeys.at(key);
}

void Keyboard::update(GLFWwindow *window, int key)
{
    if (key == GLFW_KEY_UNKNOWN)
        return;

    pressedKeys[key] = (glfwGetKey(window, key) == GLFW_PRESS);
}

} // namespace Input
