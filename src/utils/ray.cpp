#include "ray.hpp"

Ray::Ray(const glm::vec3& position, const glm::vec3& front)
    : rayStart(position),
    rayEnd(position),
    lastRay(position),
    direction(front)
{}

void Ray::step()
{
    auto forwardsVector = [](const glm::vec3& rotation)
    {
        float yaw = glm::radians(rotation.y + 90);
        float pitch = glm::radians(rotation.x);

        float x = glm::cos(yaw) * glm::cos(pitch);
        float y = glm::sin(pitch);
        float z = glm::cos(pitch) * glm::sin(yaw);

        return glm::vec3{-x, -y, -z};
    };

    lastRay = rayEnd;
    rayEnd += forwardsVector(direction) / 4.0f;
}

const glm::vec3& Ray::getEnd() const
{
    return rayEnd;
}

const glm::vec3& Ray::getLast() const
{
    return lastRay;
}

float Ray::getLength() const
{
    return glm::length(rayEnd - rayStart);
}