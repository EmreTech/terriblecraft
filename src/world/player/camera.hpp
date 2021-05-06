#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

namespace World::Player
{

const float YAW = -90.0f, PITCH = 0.0f;
const float SPEED = 2.5, SENSITIVITY = 0.2f;

struct Camera
{
    // Camera Attributes
    glm::vec3 Position;
    glm::vec3 Front{0.0f, 0.0f, -1.0f};
    glm::vec3 Up{0.0f, 1.0f, 0.0f};
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // Euler Angles (meaning mouse movement)
    float Yaw, Pitch;
    // Camera options
    float MovementSpeed = SPEED, MouseSens = SENSITIVITY;

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

    glm::mat4 ViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    void Keyboard(int direction, float deltaTime);
    void Mouse(float xoffset, float yoffset, bool constrainPitch = true);

    private:
    void updateVectors();
};

} // namespace World::Player

#endif