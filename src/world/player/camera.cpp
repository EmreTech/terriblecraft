#include "camera.hpp"

namespace World::Player {

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) {
  Position = position;
  WorldUp = up;
  Yaw = yaw;
  Pitch = pitch;
  curY = Position.y + 1.0f;
  updateVectors();
}

void Camera::Keyboard(int direction, float deltaTime) {
  float velocity = MovementSpeed * deltaTime;

  switch (direction) {
  case 0: // Forward
    Position += Front * velocity;
    break;

  case 1: // Backward
    Position -= Front * velocity;
    break;

  case 2: // Left
    Position -= Right * velocity;
    break;

  case 3: // Right
    Position += Right * velocity;
    break;

  default:
    std::cout << "Invalid direction number. Ignoring." << '\n';
    break;
  }

  //Position.y = curY;
}

void Camera::Mouse(float xoffset, float yoffset, bool constrainPitch) {
  xoffset *= MouseSens;
  yoffset *= MouseSens;

  Yaw += xoffset;
  Pitch += yoffset;

  if (constrainPitch) {
    if (Pitch > 89.0f)
      Pitch = 89.0f;
    if (Pitch < -89.0f)
      Pitch = -89.0f;
  }

  Yaw = std::fmod(Yaw, 360.0f);

  updateVectors();
}

void Camera::updateVectors() {
  // calculate the new Front vector
  glm::vec3 front;
  front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
  front.y = sin(glm::radians(Pitch));
  front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
  Front = glm::normalize(front);
  // also re-calculate the Right and Up vector
  Right = glm::normalize(glm::cross(
      Front, WorldUp)); // normalize the vectors, because their length gets
                        // closer to 0 the more you look up or down which
                        // results in slower movement.
  Up = glm::normalize(glm::cross(Right, Front));
}

} // namespace World::Player