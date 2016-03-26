#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

class Entity
{
public:
    virtual void draw(glm::mat4 view) const = 0;

    virtual void translate(const glm::vec3& amount) = 0;
    virtual void transform(const glm::mat4& amount) = 0;

    virtual void setColor(glm::vec3 rgb, unsigned int index = 0) = 0;
    virtual glm::vec3 getColor(unsigned int index = 0) const = 0;

    virtual void setPosition(glm::vec3 pos, unsigned int index = 0) = 0;
    virtual glm::vec3 getPosition(unsigned int index = 0) const = 0;
};

#endif