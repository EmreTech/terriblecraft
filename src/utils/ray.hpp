#ifndef RAY_HPP
#define RAY_HPP

#include "glm_include.hpp"

struct Ray
{
    Ray(const glm::vec3& position, float yaw, float pitch);

    void step(float amount);

    const glm::vec3& getEnd() const;
    float getLength() const;

    private:
    glm::vec3 rayStart;
    glm::vec3 rayEnd;

    float Yaw;
    float Pitch;
};

#endif