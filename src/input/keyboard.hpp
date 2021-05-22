#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <GLFW/glfw3.h>

#include <map>

#include "../utils/singleton.hpp"

namespace Input
{

struct Keyboard : public Singleton
{
    static Keyboard& getInstance();
    bool getPressedKey(int key);

    void update(GLFWwindow *window, int key);

    private:
    Keyboard() = default;
    std::map<int, bool> pressedKeys;
};

} // namespace Input


#endif