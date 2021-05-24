#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "utils/glm_include.hpp"
#include "entity/entity.hpp"

struct Camera
{
    glm::vec3 position;
    glm::vec3 rotation;

    Camera();

    void update();

    void hookEntity(Entity &entity);
    void unhookEntity();

    const glm::mat4& ViewMatrix() const;
    const glm::mat4& ProjMatrix() const;

    private:
    Entity *ptEntity = nullptr;

    glm::mat4 projectionMatrix{1.0f};
    glm::mat4 viewMatrix{1.0f};
};

#endif