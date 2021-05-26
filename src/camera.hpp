#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "utils/glm_include.hpp"
#include "utils/constants.hpp"
#include "entity/entity.hpp"

struct Camera
{
    glm::vec3 position{0.0f};
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    glm::vec3 rotation{0.0f};

    Camera();
    ~Camera();

    void update();

    void hookEntity(Entity &entity);
    void unhookEntity();

    const glm::mat4& ViewMatrix() const;
    const glm::mat4& ProjMatrix() const;

    private:
    void updateVectors();

    Entity *ptEntity = nullptr;

    glm::mat4 projectionMatrix{1.0f};
    glm::mat4 viewMatrix{1.0f};
};

#endif