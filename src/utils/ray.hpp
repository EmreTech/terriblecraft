#ifndef RAY_HPP
#define RAY_HPP

#include "glm_include.hpp"

struct Ray
{
    Ray(const glm::vec3& position, const glm::vec3& front);

    void step();

    const glm::vec3& getEnd() const;
    const glm::vec3& getLast() const;

    float getLength() const;

    private:
    glm::vec3 rayStart;
    glm::vec3 rayEnd;
    glm::vec3 lastRay;

    glm::vec3 direction;
};

#endif