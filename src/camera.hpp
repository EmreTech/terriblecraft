#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "utils/glm_include.hpp"
#include "entity/entity.hpp"

struct Camera : public Entity
{
    glm::vec3 Front{0.0f, 0.0f, -1.0f};
    glm::vec3 Up{0.0f, 1.0f, 0.0f};
    glm::vec3 Right;
    glm::vec3 WorldUp{0.0f, 1.0f, 0.0f};

    Camera();

    void update();

    void hookEntity(Entity &entity);
    void unhookEntity();

    const glm::mat4& ViewMatrix() const;
    const glm::mat4& ProjMatrix() const;

    private:
    void makeViewMatrix();

    Entity *ptEntity = nullptr;

    glm::mat4 projectionMatrix{1.0f};
    glm::mat4 viewMatrix{1.0f};
};

#endif