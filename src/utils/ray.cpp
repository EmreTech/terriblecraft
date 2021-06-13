#include "ray.hpp"

#include "maths.hpp"

Ray::Ray(const glm::vec3& position, const glm::vec3& front)
    : rayStart(position),
    rayEnd(position),
    lastRay(position),
    direction(front)
{}

void Ray::step()
{
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