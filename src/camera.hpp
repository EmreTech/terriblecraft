#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "utils/glm_include.hpp"
#include "entity/entity.hpp"

enum class ProjectionType
{
    PERSPECTIVE,
    ORTHOGRAPHIC
};

struct Camera : public Entity
{
    Camera();

    void setProjType(const ProjectionType &newType);
    void update();

    void hookEntity(Entity &entity);
    void unhookEntity();

    const glm::mat4& ViewMatrix() const;
    const glm::mat4& ProjMatrix() const;

    private:
    void makeViewMatrix();

    Entity *ptEntity = nullptr;

    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;

    ProjectionType type;
};

#endif