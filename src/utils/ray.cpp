#include "ray.hpp"

Ray::Ray(const glm::vec3& position, float yaw, float pitch)
    : rayStart(position),
    rayEnd(position),
    Yaw(glm::radians(yaw)),
    Pitch(glm::radians(pitch))
{}

void Ray::step(float amount)
{
    rayEnd.x -= glm::cos(Yaw)   * amount;
    rayEnd.z -= glm::sin(Yaw)   * amount;
    rayEnd.y -= glm::tan(Pitch) * amount;
}

const glm::vec3& Ray::getEnd() const
{
    return rayEnd;
}

float Ray::getLength() const
{
    return glm::distance(rayStart, rayEnd);
}