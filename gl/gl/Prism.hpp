#ifndef PRISM_HPP
#define PRISM_HPP

#include "Rectangle.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>

class Prism : public Entity
{
public:   
    Prism(const glm::vec3& bottomLeft
        , const float sideLength
        , const float height
        , const glm::vec3& color);

    virtual void draw(glm::mat4 view) const override;

    virtual void setColor(glm::vec3 rgb, unsigned int index = 0) override;
    virtual glm::vec3 getColor(unsigned int index = 0) const override;

    virtual void translate(const glm::vec3& amount) override;
    virtual void transform(const glm::mat4& amount) override;

    /**
    * index is unused. Returns the color of the bottom left corner.
    */
    virtual void setPosition(glm::vec3 pos, unsigned int index = 0) override;
    /**
     * index is unused. Returns the bottom left corner.
     */
    virtual glm::vec3 getPosition(unsigned int index = 0) const override;
private:
    enum Indices { BASE, LEFT, FRONT, RIGHT, BACK, TOP, NUM_SIDES };

    std::array<std::unique_ptr<Rectangle>, Indices::NUM_SIDES> sides;
};

#endif